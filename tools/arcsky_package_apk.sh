#!/usr/bin/env bash
#
# Copy a freshly built APK to a descriptive, versioned filename.
#
#   Usage: tools/arcsky_package_apk.sh [BUILD_DIR] [OUTPUT_DIR]
#
#     BUILD_DIR   where you built. If omitted, looks in the current directory
#                 and then in Qt Creator's build-* dirs beside the repo.
#     OUTPUT_DIR  where to put the named copy (defaults to a package/ dir in the
#                 build that produced the APK)
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

BUILD_DIR_ARG=${1:-}
OUTPUT_DIR_ARG=${2:-}

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
    GIT_HASH=$(git -C "$REPO_DIR" rev-parse --short HEAD 2>/dev/null || true)
    if [ -n "$GIT_HASH" ]; then
        SUFFIX="-dev-$GIT_HASH"
        echo "Dev build: v$VERSION-dev ($GIT_HASH) - HEAD is not tagged v$VERSION"
    else
        SUFFIX="-dev"
        echo "Dev build: v$VERSION-dev - no git info available for $REPO_DIR"
    fi
fi

# Prefer the signed release APK, then any APK, newest first. Takes one or more
# directories to search.
find_apk() {
    local apk
    apk=$(find "$@" -name '*-release-signed.apk' -type f -printf '%T@ %p\n' 2>/dev/null \
            | sort -rn | head -n1 | cut -d' ' -f2-)
    if [ -z "$apk" ]; then
        apk=$(find "$@" -name '*.apk' -type f -printf '%T@ %p\n' 2>/dev/null \
                | sort -rn | head -n1 | cut -d' ' -f2-)
    fi
    printf '%s' "$apk"
}

if [ -n "$BUILD_DIR_ARG" ]; then
    APK=$(find_apk "$BUILD_DIR_ARG")
    SEARCHED=$BUILD_DIR_ARG
else
    # No directory given: look in the current directory first, which covers
    # running this from inside the build dir.
    APK=$(find_apk "$PWD")
    SEARCHED=$PWD

    # Then Qt Creator's shadow build dirs, which sit beside the repo as
    # ~/build-qgroundcontrol-Android_Qt_..._Release rather than inside it.
    if [ -z "$APK" ]; then
        shadow_dirs=()
        for d in "$REPO_DIR"/../build-*; do
            [ -d "$d" ] && shadow_dirs+=("$d")
        done
        if [ ${#shadow_dirs[@]} -gt 0 ]; then
            APK=$(find_apk "${shadow_dirs[@]}")
            SEARCHED="$SEARCHED and $REPO_DIR/../build-*"
        fi
    fi
fi

if [ -z "$APK" ]; then
    echo "error: no .apk found in $SEARCHED" >&2
    echo "       pass the build directory explicitly: $0 <BUILD_DIR>" >&2
    exit 1
fi

# Default the output next to the build that produced the APK, not into the repo.
if [ -z "$OUTPUT_DIR_ARG" ]; then
    case "$APK" in
        */android-build/*) OUTPUT_DIR="${APK%%/android-build/*}/package" ;;
        *)                 OUTPUT_DIR="$(dirname "$APK")/package" ;;
    esac
else
    OUTPUT_DIR=$OUTPUT_DIR_ARG
fi

BUILD_DATE=$(date +%Y%m%d)
APK_NAME="ArcskyControl-v${VERSION}${SUFFIX}-${BUILD_DATE}.apk"

mkdir -p "$OUTPUT_DIR"
cp "$APK" "$OUTPUT_DIR/$APK_NAME"

echo "Source: $APK"
echo "Packaged: $OUTPUT_DIR/$APK_NAME"
