#!/usr/bin/env bash
set -e

MODE=${1:-debug}

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
ANDROID_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
PROJECT_DIR="$(cd "$SCRIPT_DIR/../../.." && pwd)"

# ABI które obsługujemy
ABIS=("arm64-v8a")
# ABIS=("arm64-v8a" "x86_64")

JNI_DIR="$SCRIPT_DIR/app/src/main/jniLibs"

echo "Assembling APK ($MODE)"
echo "Android dir: $ANDROID_DIR"

rm -rf "$JNI_DIR"
mkdir -p "$JNI_DIR"

for ABI in "${ABIS[@]}"; do
    SRC_DIR="$ANDROID_DIR/$ABI/bin"
    DST="$JNI_DIR/$ABI"

    if [ ! -d "$SRC_DIR" ]; then
        echo "Missing dir: $SRC_DIR"
        exit 1
    fi

    mkdir -p "$DST"
    cp -a "$SRC_DIR/"*.so "$DST/" 2>/dev/null
done

cd "$SCRIPT_DIR"

if [ "$MODE" = "release" ]; then
    ./gradlew clean assembleRelease
else
    ./gradlew clean assembleDebug
fi

echo
echo "APK generated:"
echo "$SCRIPT_DIR/app/build/outputs/apk/$MODE/app-$MODE.apk"