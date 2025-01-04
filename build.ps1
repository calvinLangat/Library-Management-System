# Check if a compiler argument was provided
if ($args.Count -eq 0) {
    Write-Host "Usage: build.ps1 [gcc|msvc]"
    exit 1
}

# Ensure the bin, obj, and debug directories exist
if (-not (Test-Path "bin")) {
    New-Item -ItemType Directory -Path "bin"
}
if (-not (Test-Path "bin\obj")) {
    New-Item -ItemType Directory -Path "bin\obj"
}
if (-not (Test-Path "bin\debug")) {
    New-Item -ItemType Directory -Path "bin\debug"
}

# Set source files
$file1 = "src\main.c"
$file2 = "src\database.c"
$file3 = "src\windowsAPI.c"

# Check for GCC or MSVC selection
if ($args[0].ToLower() -eq "gcc") {
    Write-Host "Compiling with GCC..."
    $compileCommand = "gcc -o bin\test_Library.exe $file1 $file2 $file3 -Wall -g"
    Invoke-Expression $compileCommand

    if ($?) {
        Write-Host "Compilation successful. Output: bin\test_Library.exe"
    } else {
        Write-Host "GCC compilation failed."
        exit 1
    }
} elseif ($args[0].ToLower() -eq "msvc") {
    Write-Host "Compiling with MSVC..."

    # Set up MSVC environment
    $vcvarsBatch = "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat"
    if (-Not (Test-Path $vcvarsBatch)) {
        Write-Host "Failed to find vcvarsall.bat. Ensure the path is correct."
        exit 1
    }
    & $vcvarsBatch x64

    # Compile source files into object files with debugging information
    $compileCommand = "cl /Fo:bin\obj\ /Zi /Fd:bin\debug\test_Library.pdb /c $file1 $file2 $file3"
    Invoke-Expression $compileCommand

    if ($?) {
        Write-Host "Object files created successfully."
    } else {
        Write-Host "Compilation to object files failed."
        exit 1
    }

    # Link object files into executable with debugging information
    $linkCommand = "cl /Fe:bin\test_Library.exe bin\obj\*.obj /Zi /Fd:bin\debug\test_Library.pdb"
    Invoke-Expression $linkCommand

    if ($?) {
        Write-Host "Linking successful. Output: bin\test_Library.exe"
    } else {
        Write-Host "Linking failed."
        exit 1
    }

    # Clean up object files
    Remove-Item "bin\obj\*.obj" -Force
    Write-Host "Cleaning up object files."
} else {
    Write-Host "Invalid compiler selection. Use 'gcc' or 'msvc'."
    exit 1
}
