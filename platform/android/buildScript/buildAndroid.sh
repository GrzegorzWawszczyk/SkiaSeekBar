#!/usr/bin/env bash
set -e

MODE=${1:-debug}

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR="$(cd "$SCRIPT_DIR/../../.." && pwd)"     # główny katalog projektu
BUILD_DIR="$PROJECT_DIR/build/android"

# obsługiwane architektury
declare -A ABIS
ABIS=( ["arm64-v8a"]="arm64-android" ["x86_64"]="x64-android" )

for ABI in "${!ABIS[@]}"; do
    TRIPLET=${ABIS[$ABI]}
    BUILD_ABI_DIR="$BUILD_DIR/$ABI"

    echo "=== Configuring $ABI ($MODE) ==="
    cmake -S "$PROJECT_DIR" \
          -B "$BUILD_ABI_DIR" \
          -G Ninja \
          -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" \
          -DVCPKG_CHAINLOAD_TOOLCHAIN_FILE="$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake" \
          -DVCPKG_TARGET_TRIPLET="$TRIPLET" \
          -DCMAKE_SYSTEM_NAME=Android \
          -DANDROID_NDK="$ANDROID_NDK_HOME" \
          -DPLATFORM=android \
          -DANDROID_ABI="$ABI" \
          -DANDROID_PLATFORM=android-28 \
          -DCMAKE_BUILD_TYPE="$MODE"

    echo "=== Building $ABI ($MODE) ==="
    cmake --build "$BUILD_ABI_DIR" --config "$MODE"
done

echo
echo "=== Assembling APK ($MODE) ==="
$BUILD_DIR/apk/assembleApk.sh "$MODE"