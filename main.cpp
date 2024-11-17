// #include "imgui-1.91.5\imgui.h"
// #include "imgui-1.91.5\misc\cpp\imgui_stdlib.h"
// #include "imgui-1.91.5\backends\imgui_impl_win32.h"
// #include "imgui-1.91.5\backends\imgui_impl_opengl3.h"
// #include "imgui-1.91.5\backends\imgui_impl_opengl3_loader.h"

#include "imgui.h"
#include "imgui_stdlib.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_opengl3_loader.h"

#include "combat-data.h" //I added it the game-library folder into the INCLUDE in the .bat file, it'll be fine
#include "queue_stack.h"

#include <windows.h>
#include <GL/GL.h>
#include <tchar.h>

#include <iostream>
#include <string>
#include <sstream>
#include <chrono>

// #include "stack.h"
// #include "queue.h"

// Data stored per platform window
struct WGL_WindowData 
{
    HDC hDC;

};

// Data
static HGLRC            g_hRC;
static WGL_WindowData   g_MainWindow;
static int              g_Width;
static int              g_Height;

// Helper functions
bool CreateDeviceWGL(HWND hWnd, WGL_WindowData* data)
{
    HDC hDc = ::GetDC(hWnd);
    PIXELFORMATDESCRIPTOR pfd = { 0 };
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;

    const int pf = ::ChoosePixelFormat(hDc, &pfd);
    if (pf == 0)
        return false;
    if (::SetPixelFormat(hDc, pf, &pfd) == FALSE)
        return false;
    ::ReleaseDC(hWnd, hDc);

    data->hDC = ::GetDC(hWnd);
    if (!g_hRC)
        g_hRC = wglCreateContext(data->hDC);
    return true;
}

void CleanupDeviceWGL(HWND hWnd, WGL_WindowData* data)
{
    wglMakeCurrent(nullptr, nullptr);
    ::ReleaseDC(hWnd, data->hDC);
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (wParam != SIZE_MINIMIZED)
        {
            g_Width = LOWORD(lParam);
            g_Height = HIWORD(lParam);
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}

constexpr ImVec4 GREEN = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
constexpr ImVec4 RED = ImVec4(0.8f, 0.0f, 0.0f, 1.0f);
constexpr ImVec4 BLACK = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
constexpr ImVec4 GRAY = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);
constexpr ImVec4 LIGHT_GRAY = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
constexpr float TABLE_ROW_HEIGHT = 27.0;

enum class Spells {
    MAGIC_MISSILE = 0,
    FLAMETHROWER,
    WATERGUN,
    SAP_LIFE,

};

Enemy viewEnemy (Queue queue, int placementIndex=0) {
    Enemy enemy;
  
    if (placementIndex != 0) {
        for (int counter{0}; counter < placementIndex; counter++) {
            queue.dequeue(true);

        }

    }

    enemy = queue.peek();

    return enemy;

}

void showCharacterHealth (Player *player) {

    if (player->getCurrentHealth() <= player->getCriticalHealth()) {
        ImGui::Text("Player HP: ");
        ImGui::SameLine();
        ImGui::TextColored(RED, "%d/%d", player->getCurrentHealth(), player->getMaxHealth());
        

    } else {
        ImGui::Text("Player HP:  %d/%d", player->getCurrentHealth(), player->getMaxHealth());

    }
    
}

void showCharacterHealth (Enemy enemy, bool isFront=false) {
    if (!isFront) {
        ImGui::TextDisabled("%s's HP:  %d/%d", enemy.getName().c_str(), enemy.getCurrentHealth(), enemy.getMaxHealth());

    } else if (enemy.getCurrentHealth() <= enemy.getCriticalHealth()) {
        ImGui::Text("%s's HP: ", enemy.getName().c_str());
        ImGui::SameLine();
        ImGui::TextColored(RED, "%d/%d", enemy.getCurrentHealth(), enemy.getMaxHealth());

    } else {
        ImGui::Text("%s's HP:  %d/%d", enemy.getName().c_str(), enemy.getCurrentHealth(), enemy.getMaxHealth());

    }

}

void showPlayerMana (Player *player) {
    ImGui::Text("Player MN:  %d/%d", player->getCurrentMana(), player->getMaxMana());

}

// void showCharacterHealth (Enemy *enemy, bool isFront=false) {
//     if (!isFront) {
//         ImGui::TextDisabled("%s's HP:  %d/%d", enemy->getName().c_str(), enemy->getCurrentHealth(), enemy->getMaxHealth());

//     } else if (enemy->getCurrentHealth() <= enemy->getCriticalHealth()) {
//         ImGui::Text("%s's HP: ", enemy->getName().c_str());
//         ImGui::SameLine();
//         ImGui::TextColored(RED, "%d/%d", enemy->getCurrentHealth(), enemy->getMaxHealth());

//     } else {
//         ImGui::Text("%s's HP:  %d/%d", enemy->getName().c_str(), enemy->getCurrentHealth(), enemy->getMaxHealth());

//     }

// }

bool isEnemyTurn (bool isPlayerTurn, std::chrono::time_point<std::chrono::system_clock> lastTurn) {
    if (isPlayerTurn) {
        return false;

    }

    if (std::chrono::system_clock::now() - lastTurn > std::chrono::duration<double>(2.0)) {
        return true;
    }

    return false;
}

void castSpell (Player *player, Enemy *enemy, Spell spell) {
    int spellAttackValue;
    // float attackBonus;
    // Type attackType;
    // int healValue;

    // switch(static_cast<Spells>(spellIndex)) {
    //     case Spells::MAGIC_MISSILE:
    //         attackBonus = 0;
    //         attackType = Type::NORMAL;
    //         break;

    //     case Spells::FLAMETHROWER:
    //         attackBonus = 0.5;
    //         attackType = Type::FIRE;
    //         break;
            
    //     case Spells::WATERGUN:
    //         attackBonus = 0.3;
    //         attackType = Type::WATER;
    //         break;

    //     case Spells::SAP_LIFE:
    //         attackBonus = -0.1;
    //         attackType = Type::GRASS;
    //         break;


    // }

    if (spell.getCost() > player->getCurrentMana()) {
        return;

    }

    spellAttackValue = player->getAttack() + (player->getAttack() * spell.getAttackBonus());

    if (spell.getType() == Type::GRASS) {
        player->heal(enemy->takeDamage(spellAttackValue, spell.getType()) >> 1);

    } else {
        enemy->takeDamage(spellAttackValue, spell.getType());

    }

    player->consumeMana(spell.getCost());

}



int main () {
    // Create application window
    //ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEXW wc = { sizeof(wc), CS_OWNDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"ImGui Example", nullptr };
    ::RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"The Time Travelling Wizard", WS_OVERLAPPEDWINDOW, 100, 100, 640, 400, nullptr, nullptr, wc.hInstance, nullptr);

    // Initialize OpenGL
    if (!CreateDeviceWGL(hwnd, &g_MainWindow))
    {
        CleanupDeviceWGL(hwnd, &g_MainWindow);
        ::DestroyWindow(hwnd);
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }
    wglMakeCurrent(g_MainWindow.hDC, g_hRC);

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;    // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_InitForOpenGL(hwnd);
    ImGui_ImplOpenGL3_Init();

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != nullptr);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = GRAY;

    // Game-related declarations
    static bool buttonsDisabled{false};
     
    static bool gameWon{false};
    static bool gameLost{false};
    static int gameScore{10000};

    static bool isPlayerTurn{true};
    static std::chrono::time_point<std::chrono::system_clock> lastTurn = std::chrono::system_clock::now(); // should be 2 seconds after this before the enemy makes a move
    
    static Spell spells[] = {
        Spell("Magic Missile", 5, 0.0, NORMAL), 
        Spell("Fireball", 8, 0.5, FIRE), 
        Spell("Watercannon", 6, 0.3, WATER), 
        Spell("Leech Life", 7, -0.1, GRASS)
    
    };
    static int spellSelected{0};

    static Queue *enemyQueue = new Queue();
    enemyQueue->enqueue(Enemy(FIRE, Size::MEDIUM, 5, "MAGMA DEMON"));
    enemyQueue->enqueue(Enemy(GRASS, Size::MEDIUM, 3, "FOREST DEMON"));
    enemyQueue->enqueue(Enemy(WATER, Size::MEDIUM, 3, "OCEAN DEMON"));

    static Player *player = new Player(100, 50, NORMAL);
    Enemy currentEnemyValue = enemyQueue->peek();
    Enemy *currentEnemy = &currentEnemyValue;

    Enemy secondEnemyPreview = viewEnemy(*enemyQueue, 1);
    Enemy lastEnemyPreview = viewEnemy(*enemyQueue, 2);


    // Main loop
    bool done = false;
    while (!done)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // See the WndProc() function below for our to dispatch events to the Win32 backend.
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }

        if (done)
            break;
        
        if (::IsIconic(hwnd))
        {
            ::Sleep(10);
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

            // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {

            ImGui::Begin("Game Window");

                if (gameWon | gameLost) {
                    ImGui::TextColored(LIGHT_GRAY, "GAME OVER");

                } else if (isPlayerTurn) {
                    ImGui::TextColored(GREEN, "Player's turn...");
                    clear_color = BLACK;
                    // buttonsDisabled = false;

                } else {
                    ImGui::TextColored(RED, "%s's turn...", currentEnemy->getName().c_str());
                    clear_color = RED; 

                }

                ImGui::BeginTable("MainInterface", 2);
                    ImGui::TableNextRow(0, TABLE_ROW_HEIGHT);
                        ImGui::TableSetColumnIndex(0);
                            showCharacterHealth(player);

                        ImGui::TableSetColumnIndex(1);
                            showCharacterHealth(currentEnemyValue, true);

                    ImGui::TableNextRow(0, TABLE_ROW_HEIGHT);
                        ImGui::TableSetColumnIndex(0);

                        ImGui::TableSetColumnIndex(1);
                            showCharacterHealth(secondEnemyPreview);

                    ImGui::TableNextRow(0, TABLE_ROW_HEIGHT);
                        ImGui::TableSetColumnIndex(0);
                            showPlayerMana(player);

                        ImGui::TableSetColumnIndex(1);
                            showCharacterHealth(lastEnemyPreview);

                    ImGui::TableNextRow(0, TABLE_ROW_HEIGHT);
                        ImGui::TableSetColumnIndex(0);
                            if (buttonsDisabled) {
                                ImGui::BeginDisabled();

                            }

                            if (ImGui::Button("Cast Spell") & !buttonsDisabled) {
                                castSpell(player, currentEnemy, spells[spellSelected]);
                                isPlayerTurn = false;
                                lastTurn = std::chrono::system_clock::now();

                            } 

                            if (buttonsDisabled) {
                                ImGui::EndDisabled();

                            }


                        ImGui::TableSetColumnIndex(1);
                            static ImGuiComboFlags comboFlags = 0;
                            comboFlags &= ~ImGuiComboFlags_NoPreview; 

                            if (ImGui::BeginCombo("", spells[spellSelected].getName().c_str(), comboFlags)) {
                                for (int index{0}; index < IM_ARRAYSIZE(spells); index++) {
                                        static bool is_selected = (spellSelected == index);
                                        
                                        if (ImGui::Selectable(spells[index].getLabel().c_str())) {
                                            spellSelected = index;

                                        }

                                        if (is_selected) {
                                                ImGui::SetItemDefaultFocus();

                                        }

                                }
                                ImGui::EndCombo();

                            }
                    ImGui::TableNextRow(0, TABLE_ROW_HEIGHT);
                        ImGui::TableSetColumnIndex(0);
                            if (buttonsDisabled) {
                                ImGui::BeginDisabled();

                            }

                            if (ImGui::Button("Rewind") & isPlayerTurn) {
                                
                                isPlayerTurn = false;
                                lastTurn = std::chrono::system_clock::now();

                            }

                            if (buttonsDisabled) {
                                ImGui::EndDisabled();

                            }

                        ImGui::TableSetColumnIndex(1);

                ImGui::EndTable();

                if (isPlayerTurn) {
                    buttonsDisabled = false;

                } else {
                    buttonsDisabled = true;

                }

                if (isEnemyTurn(isPlayerTurn, lastTurn) & !(gameWon | gameLost)) {
                    player->takeDamage(currentEnemy->getAttack(), currentEnemy->getType());
                    player->recoverMana();
                    isPlayerTurn = true;
                    buttonsDisabled = false;

                } 

                if (currentEnemy->isDefeated()) {
                    gameWon = true;

                } else if (player->isDefeated()) {
                    gameLost = true;

                }

                // ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        if (gameWon | gameLost) {
            buttonsDisabled = true;

            ImGui::Begin("GAME OVER");
                ImGui::Text(((gameWon) ? "You won!" : "You lost!"));
            ImGui::End();

        } 

        // Rendering
        ImGui::Render();
        glViewport(0, 0, g_Width, g_Height);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Present
        ::SwapBuffers(g_MainWindow.hDC);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceWGL(hwnd, &g_MainWindow);
    wglDeleteContext(g_hRC);
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;

}