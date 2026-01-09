param(
    [string]$Mode = "Debug",
    [switch]$Build
)

# Ścieżki
$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$ProjectDir = Resolve-Path "$ScriptDir/../../.."
$BuildDir = "$ProjectDir/build/windows"

Write-Host "=== Configuring Windows ($Mode) ==="
Write-Host "Project dir: $ProjectDir"
Write-Host "Build dir: $BuildDir"

# Sprawdź VCPKG_ROOT
if (-not $env:VCPKG_ROOT) {
    Write-Error "VCPKG_ROOT not set!"
    exit 1
}

# CMake configure
cmake -S $ProjectDir -B $BuildDir `
    -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT\scripts\buildsystems\vcpkg.cmake" `
    -DVCPKG_TARGET_TRIPLET="x64-windows" `
    -DPLATFORM="windows" `
    -DCMAKE_BUILD_TYPE=$Mode

Write-Host "Configuration done."

if ($Build) {
    Write-Host "=== Building ($Mode) ==="
    cmake --build $BuildDir --config $Mode
    Write-Host "Build finished."
} else {
    Write-Host "To build, run:"
    Write-Host "cmake --build $BuildDir --config $Mode"
}
