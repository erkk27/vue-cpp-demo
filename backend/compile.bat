@echo off
echo Compiling C++ Backend...

REM Compile using GCC
g++ -std=c++17 -Wall -Wextra -o cpp_backend main.cpp -lws2_32 -lpthread

if %ERRORLEVEL% EQU 0 (
    echo Compilation successful!
    echo You can now run the server with: .\cpp_backend.exe
) else (
    echo Compilation failed!
)

pause 