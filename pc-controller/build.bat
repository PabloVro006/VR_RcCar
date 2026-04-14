@echo off
setlocal

echo === Configuring project ===
cmake -B build -G Ninja

if errorlevel 1 (
    echo CMake configure failed
    pause
    exit /b 1
)

echo === Building project ===
cmake --build build

if errorlevel 1 (
    echo Build failed
    pause
    exit /b 1
)

echo === Build completed successfully ===
pause