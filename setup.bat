@echo off
echo ========================================
echo YM2203Synth VST3 Plugin Setup
echo ========================================

if not exist "C:\JUCE" (
    echo ERROR: JUCE not found at C:\JUCE
    echo Please install JUCE first from https://juce.com/download/
    pause
    exit /b 1
)

echo.
echo [1/3] Creating project directories...
mkdir Source\YM2203_Emulator
mkdir Source\VGZParser
mkdir Source\Plugin
mkdir Builds

echo [2/3] Validating Visual Studio 2022 installation...
if not exist "C:\Program Files\Microsoft Visual Studio\2022" (
    echo WARNING: Visual Studio 2022 not found
    echo Please ensure Visual Studio 2022 is installed
)

echo [3/3] Opening Projucer...
start "C:\JUCE\extras\Projucer\Builds\VisualStudio2022\x64\Release\Projucer.exe"

echo.
echo ========================================
echo Setup Complete!
echo ========================================
echo.
echo Next steps:
echo 1. In Projucer: File ^> Global Paths
echo 2. Set JUCE Path to: C:\JUCE
echo 3. Open YM2203Synth.jucer
echo 4. Select: File ^> Save Project and Open in IDE
echo 5. Visual Studio will open the project
echo 6. Build ^> Build Solution (Ctrl+Shift+B)
echo.
pause
