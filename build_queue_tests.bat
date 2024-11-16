@set OUT_DIR=Debug
@set OUT_EXE=queue-test
@set SOURCES=game-library\combat-data.cpp game-library\stack.cpp game-library\queue.cpp
g++ %SOURCES% -o %OUT_DIR%\%OUT_EXE%.exe
