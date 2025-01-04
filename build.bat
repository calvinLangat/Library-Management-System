@echo off
:: Check if a compiler argument was provided
if "%1"=="" (
    echo Usage: compile.bat [gcc|msvc]
    exit /b 1
)

:: Ensure the bin and obj directories exist
if not exist bin (
    mkdir bin
)
if not exist bin\obj (
    mkdir bin\obj
)

:: Set source files
set file1=src/main.c
set file2=src/database.c
set file3=src/windowsAPI.c

:: Check for GCC or MSVC selection
if /i "%1"=="gcc" (
    echo Compiling with GCC...
    gcc -o bin/test_Library.exe %file1% %file2% %file3% -Wall -g
    if %errorlevel% neq 0 (
        echo GCC compilation failed.
        exit /b 1
    )
    echo Compilation successful. Output: bin\test_Library.exe
) else if /i "%1"=="msvc" (
    echo Compiling with MSVC...
    call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
    if %errorlevel% neq 0 (
        echo Failed to set up MSVC environment. Ensure the path to vcvarsall.bat is correct.
        exit /b 1
    )
    
    :: Compile source files into object files with debugging information
    cl /Fo:bin\obj\ /Zi /Fd:bin\debug\test_Library.pdb /c %file1% %file2% %file3%
    if %errorlevel% neq 0 (
        echo Compilation to object files failed.
        exit /b 1
    )
    
    :: Link object files into executable with debugging information
    cl /Fe:bin\test_Library.exe bin\obj\*.obj /Zi /Fd:bin\debug\test_Library.pdb
    if %errorlevel% neq 0 (
        echo Linking failed.
        exit /b 1
    )
    
    
    echo Cleaning up object files...
    del /q bin\obj\*.obj
    echo Compilation successful. Output: bin\test_Library.exe
) else (
    echo Invalid compiler selection. Use "gcc" or "msvc".
    exit /b 1
)
