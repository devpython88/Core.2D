#!/bin/bash
set -e

# === Argument checks ===
if [ -z "$1" ]; then
    echo "No dist directory name provided [arg 1]"
    exit 1
fi
DIST_DIR="$1"

if [ -z "$2" ]; then
    echo "No cmake generator provided [arg 2]"
    exit 1
fi
BUILD_GEN="$2"

if [ -z "$3" ]; then
    echo "No build system executable provided [arg 3]"
    exit 1
fi
BUILD_SYS="$3"

PACKAGE_DIST="${4:-no}"

# === Configure and build ===
mkdir -p build-unix
cd build-unix

cmake -G "$BUILD_GEN" ..
if [ $? -ne 0 ]; then
    echo "cmake configuration failed."
    exit 1
fi

$BUILD_SYS
if [ $? -ne 0 ]; then
    echo "build failed."
    exit 1
fi

mkdir -p "$DIST_DIR/lib"
mkdir -p "$DIST_DIR/include"

# === Copy .a and .lib files to dist/lib ===
cp -f ./*.a "$DIST_DIR/lib/" 2>/dev/null || true
cp -f ./*.lib "$DIST_DIR/lib/" 2>/dev/null || true

# === Copy headers to dist/include ===
cp -f ../src/*.h "$DIST_DIR/include/" 2>/dev/null || true

echo "Distribution prepared in \"$DIST_DIR\""

# === Package into tar.gz if 4th arg is 'yes' ===
if [ "$PACKAGE_DIST" = "yes" ]; then
    tar -czf "${DIST_DIR}.tar.gz" "$DIST_DIR"
    echo "Packaged ${DIST_DIR} into ${DIST_DIR}.tar.gz"
fi
