@echo off
echo Building C++ Backend with CMake...

REM Create build directory if it doesn't exist
if not exist "build" mkdir build
cd build

REM Configure with CMake
echo Configuring project...
"C:\Program Files\CMake\bin\cmake.exe" .. -G "MinGW Makefiles"

REM Build the project
echo Building project...
"C:\Program Files\CMake\bin\cmake.exe" --build .

echo Build completed!
echo You can now run the server with: .\cpp_backend.exe
pause 