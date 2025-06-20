@echo off
echo Downloading C++ dependencies...

REM Download Crow library
echo Downloading Crow library...
powershell -Command "Invoke-WebRequest -Uri 'https://raw.githubusercontent.com/CrowCpp/Crow/master/include/crow_all.h' -OutFile 'vendor\crow_all.h'"

REM Download nlohmann/json library
echo Downloading nlohmann/json library...
powershell -Command "Invoke-WebRequest -Uri 'https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp' -OutFile 'vendor\nlohmann\json.hpp'"

echo Dependencies downloaded successfully!
echo You can now build the project using build.bat
pause 