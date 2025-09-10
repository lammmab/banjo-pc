@echo off
setlocal
cls

REM === Config ===
set BUILD_DIR=build
set BIN_DIR=bin
set CONFIG=Debug
set EXE_NAME=banjo.exe

REM === Clean previous build folder ===
if exist %BUILD_DIR% (
    echo Removing old build folder...
    rmdir /s /q %BUILD_DIR%
)

REM === Create bin folder if it doesn't exist ===
if not exist %BIN_DIR% mkdir %BIN_DIR%

REM === Create build directory ===
mkdir %BUILD_DIR%
cd %BUILD_DIR%

REM === Configure project with CMake ===
echo Configuring project...
cmake -DCMAKE_BUILD_TYPE=%CONFIG% ..

REM === Build project ===
echo Building project...
cmake --build . --config %CONFIG%

if %ERRORLEVEL% NEQ 0 (
    echo Build failed!
    exit /b %ERRORLEVEL%
)

REM === Copy final executable to bin folder ===
echo Copying executable to %BIN_DIR%...
copy "%CONFIG%\%EXE_NAME%" "..\%BIN_DIR%\%EXE_NAME%"

cd ..
echo Build complete! Executable is in %BIN_DIR%\%EXE_NAME%
pause
endlocal
