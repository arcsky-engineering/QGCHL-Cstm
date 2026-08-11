#!/usr/bin/env bash
#
# Copy a freshly built APK to a descriptive, versioned filename.
#
#   Usage: tools/arcsky_package_apk.sh [BUILD_DIR] [OUTPUT_DIR]
#
#     BUILD_DIR   where you ran qmake/make (defaults to the current directory)
#     OUTPUT_DIR  where to put the named copy (defaults to BUILD_DIR/package)
#
# Produces e.g.
#   ArcskyControl-v1.0.0-20260811.apk                    (release: HEAD is on its v tag)
#   ArcskyControl-v1.0.0-dev-5c604bd77-20260811.apk      (dev build)
#
# The version is read from custom/custom.pri, so that file stays the single
# source of truth. The original APK is copied, not moved.

set -euo pipefail

SCRIPT_DIR=$(cd "$(dirname "$0")" && pwd)
REPO_DIR=$(cd "$SCRIPT_DIR/.." && pwd)
CUSTOM_PRI="$REPO_DIR/custom/custom.pri"

BUILD_DIR=${1:-$PWD}
OUTPUT_DIR=${2:-$BUILD_DIR/package}

[ -f "$CUSTOM_PRI" ] || { echo "error: cannot find $CUSTOM_PRI" >&2; exit 1; }

# Pull the version numbers out of custom.pri rather than duplicating them here.
pri_value() {
    sed -n "s/^[[:space:]]*$1[[:space:]]*=[[:space:]]*\([^[:space:]]*\).*/\1/p" "$CUSTOM_PRI" | head -n1
}

VER_MAJOR=$(pri_value ARCSKY_VER_MAJOR)
VER_MINOR=$(pri_value ARCSKY_VER_MINOR)
VER_PATCH=$(pri_value ARCSKY_VER_PATCH)

if [ -z "$VER_MAJOR" ] || [ -z "$VER_MINOR" ] || [ -z "$VER_PATCH" ]; then
    echo "error: could not parse ARCSKY_VER_* from $CUSTOM_PRI" >&2
    exit 1
fi

VERSION="$VER_MAJOR.$VER_MINOR.$VER_PATCH"

# Same release/dev rule the build uses: a release build is one where HEAD sits
# exactly on its own v<version> tag.
EXACT_TAG=$(git -C "$REPO_DIR" describe --tags --exact-match HEAD 2>/dev/null || true)
if [ "$EXACT_TAG" = "v$VERSION" ]; then
    SUFFIX=""
    echo "Release build: v$VERSION"
else
    GIT_HASH=$(git -C "$REPO_DIR" rev-parse --short HEAD)
    SUFFIX="-dev-$GIT_HASH"
    echo "Dev build: v$VERSION-dev ($GIT_HASH) - HEAD is not tagged v$VERSION"
fi

# Prefer the signed release APK, then any APK, newest first.
APK=$(find "$BUILD_DIR" -name '*-release-signed.apk' -type f -printf '%T@ %p\n' 2>/dev/null \
        | sort -rn | head -n1 | cut -d' ' -f2-)
if [ -z "$APK" ]; then
    APK=$(find "$BUILD_DIR" -name '*.apk' -type f -printf '%T@ %p\n' 2>/dev/null \
            | sort -rn | head -n1 | cut -d' ' -f2-)
fi
if [ -z "$APK" ]; then
    echo "error: no .apk found under $BUILD_DIR" >&2
    exit 1
fi

BUILD_DATE=$(date +%Y%m%d)
APK_NAME="ArcskyControl-v${VERSION}${SUFFIX}-${BUILD_DATE}.apk"

mkdir -p "$OUTPUT_DIR"
cp "$APK" "$OUTPUT_DIR/$APK_NAME"

echo "Source: $APK"
echo "Packaged: $OUTPUT_DIR/$APK_NAME"
