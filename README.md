# SkiaSeekBar

Custom C++ video seek bar with Skia & SDL3, mimicking YouTube-style segments and double-click seeking.

---

## Features

- 🎨 Rendering with [Skia](https://skia.org/) and [SDL3](https://www.libsdl.org/)
- ⏩ YouTube-style skip by double-click (10s forward/back)
- 🖱️📱 Supports mouse(desktop), and touch(android) input
- 📱💻Cross-platform: Android & Windows

---


## Getting Started

### Prerequisites

- **C++20 compiler**
- [CMake ≥ 3.21](https://cmake.org/)
- [SDL3](https://www.libsdl.org/)
- [Skia](https://skia.org/)
- [vcpkg](https://vcpkg.io/) for dependency management (VCPKG_ROOT evironment variable set is required for both supported platforms)
- Android NDK (if building for Android) (ANDROID_NDK_HOME evironment variable set is required)
- Android SDK licences accepted for building APK
- Linux or WSL for Android (at least I did it this way)

### Build (Windows)

Two build options:

1. **Manually**
```bash
cmake -S . -B build/windows `
    -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT\scripts\buildsystems\vcpkg.cmake" `
    -DVCPKG_TARGET_TRIPLET="x64-windows" `
    -DPLATFORM="windows" `
    -DCMAKE_BUILD_TYPE=$Mode
```
and then with Visual Studio or
```
cmake --build build/windows
```
2. **With script**
There's a script `buildWindows.ps1` in `platform/windows/buildScript`, usage:
```
buildWindows.ps1 (config only)
buildWindows.ps1 -Mode Relese (config only for release)
buildWindows.ps1 -Build (config and build for debug)
buildWindows.ps1 -Mode Debug -Build (config and build for debug)
```

### Build (Android)

Two build options:

1. **Manually**
```bash
cmake -S . \
  -B build/android/arm64-v8a \
  -G Ninja \
  -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" \
  -DVCPKG_CHAINLOAD_TOOLCHAIN_FILE="$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake" \
  -DVCPKG_TARGET_TRIPLET=arm64-android \
  -DCMAKE_SYSTEM_NAME=Android \
  -DANDROID_NDK="$ANDROID_NDK_HOME" \
  -DPLATFORM=android \
  -DANDROID_ABI=arm64-v8a \
  -DANDROID_PLATFORM=android-28


cmake -S . \
  -B build/android/x86_64 \
  -G Ninja \
  -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" \
  -DVCPKG_CHAINLOAD_TOOLCHAIN_FILE="$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake" \
  -DVCPKG_TARGET_TRIPLET=x64-android \
  -DCMAKE_SYSTEM_NAME=Android \
  -DANDROID_NDK="$ANDROID_NDK_HOME" \
  -DPLATFORM=android \
  -DANDROID_ABI=x86_64 \
  -DANDROID_PLATFORM=android-28
```
and then
```
cmake --build build/android/arm64-v8a
cmake --build build/android/x86_64
```
2. **With script**
There's a script `buildAndroid.sh` in `platform/android/buildScript`, usage:
```
buildAndroid.sh
buildAndroid.sh debug
buildAndroid.sh release
```
configures projects, builds them, packs to apk (in build/android/apk), with gradle and script assembleApk.sh.