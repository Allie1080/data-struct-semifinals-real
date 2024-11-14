@REM Build for MINGW64 or 32 from MSYS2. 
@set OUT_DIR=Debug
@set OUT_EXE=test
@set INCLUDES=-Iimgui-1.91.5 -Iimgui-1.91.5\backends -Iimgui-1.91.5\misc\cpp
@set SOURCES=main.cpp imgui-1.91.5\backends\imgui_impl_opengl3.cpp imgui-1.91.5\backends\imgui_impl_win32.cpp imgui-1.91.5\imgui*.cpp
@set LIBS=-lopengl32 -lgdi32 -ldwmapi
mkdir %OUT_DIR%
g++ -DUNICODE %INCLUDES% %SOURCES% -o %OUT_DIR%/%OUT_EXE%.exe --static -mwindows %LIBS% %LIBS%
