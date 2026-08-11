message("Adding Custom Herelink Plugin")

#-- Version control
#   This is the single source of truth for the Arcsky version. Upstream's
#   git-describe scheme in QGCCommon.pri never matches our tags, so the value
#   it computes (vUnknown) is discarded below.
#
#   Bump these by hand. Keep MAJOR and MINOR to one digit and PATCH to two,
#   otherwise the Android version code below runs out of room.

ARCSKY_VER_MAJOR = 1
ARCSKY_VER_MINOR = 0
ARCSKY_VER_PATCH = 0

#   The upstream QGroundControl release this fork is based on. Displayed next to
#   our version for support purposes. Update this when rebasing onto new QGC.
ARCSKY_QGC_BASE_VERSION = 4.4.1

linux {
    QMAKE_CXXFLAGS_WARN_ON += -Wno-strict-aliasing
}

ARCSKY_VERSION = $${ARCSKY_VER_MAJOR}.$${ARCSKY_VER_MINOR}.$${ARCSKY_VER_PATCH}
ARCSKY_GIT_DIR = $$PWD/../.git

# A build counts as a release build only when HEAD sits exactly on its own
# v<version> tag, e.g. "git tag v1.0.0". Everything else is a dev build and
# carries branch + short hash so any field APK can be traced back to a commit.
win32 {
    ARCSKY_GIT_EXACT_TAG = $$system(git --git-dir $$ARCSKY_GIT_DIR describe --tags --exact-match HEAD 2>nul)
} else {
    ARCSKY_GIT_EXACT_TAG = $$system(git --git-dir $$ARCSKY_GIT_DIR describe --tags --exact-match HEAD 2>/dev/null)
}

equals(ARCSKY_GIT_EXACT_TAG, v$${ARCSKY_VERSION}) {
    message("Arcsky release build: v$${ARCSKY_VERSION} (QGC $${ARCSKY_QGC_BASE_VERSION})")
} else {
    ARCSKY_GIT_BRANCH = $$system(git --git-dir $$ARCSKY_GIT_DIR rev-parse --abbrev-ref HEAD)
    ARCSKY_GIT_HASH   = $$system(git --git-dir $$ARCSKY_GIT_DIR rev-parse --short HEAD)
    ARCSKY_VERSION    = $${ARCSKY_VERSION}-dev

    # Passed separately rather than pre-joined: a define containing a space
    # doesn't survive the compiler command line reliably.
    DEFINES += ARCSKY_GIT_BRANCH_STR=\"\\\"$$ARCSKY_GIT_BRANCH\\\"\"
    DEFINES += ARCSKY_GIT_HASH_STR=\"\\\"$$ARCSKY_GIT_HASH\\\"\"

    message("Arcsky dev build: v$${ARCSKY_VERSION} (QGC $${ARCSKY_QGC_BASE_VERSION}) $${ARCSKY_GIT_BRANCH} $${ARCSKY_GIT_HASH}")
}

DEFINES -= APP_VERSION_STR=\"\\\"$$APP_VERSION_STR\\\"\"
DEFINES += APP_VERSION_STR=\"\\\"$$ARCSKY_VERSION\\\"\"
DEFINES += ARCSKY_QGC_BASE_VERSION_STR=\"\\\"$$ARCSKY_QGC_BASE_VERSION\\\"\"

AndroidBuild {
    # QGCCommon.pri already computed these from the upstream git tag, which this
    # fork doesn't use, so every APK ended up as versionCode 660000000 and
    # versionName "APP_VERSION_STR". Redo them from our version instead. custom.pri
    # is included after QGCCommon.pri, so these assignments win.
    greaterThan(ARCSKY_VER_MAJOR, 9) {
        error(Arcsky major version larger than 1 digit: $${ARCSKY_VER_MAJOR})
    }
    greaterThan(ARCSKY_VER_MINOR, 9) {
        error(Arcsky minor version larger than 1 digit: $${ARCSKY_VER_MINOR})
    }
    greaterThan(ARCSKY_VER_PATCH, 99) {
        error(Arcsky patch version larger than 2 digits: $${ARCSKY_VER_PATCH})
    }

    # Bitness prefix is 66/34 instead of 64/32 to stay compatible with the
    # upstream version code format. See QGCCommon.pri for the history.
    equals(ANDROID_TARGET_ARCH, arm64-v8a) {
        ARCSKY_ANDROID_BITNESS = 66
    } else {
        ARCSKY_ANDROID_BITNESS = 34
    }

    ARCSKY_ANDROID_PATCH = $${ARCSKY_VER_PATCH}
    lessThan(ARCSKY_ANDROID_PATCH, 10) {
        ARCSKY_ANDROID_PATCH = $$join(ARCSKY_ANDROID_PATCH, "", "0")
    }

    # Format: BBMIPP000 (B=bitness, M=major, I=minor, PP=patch). The trailing
    # three digits are reserved so a rebuild of the same version can be bumped
    # if a store/OTA ever requires a unique code.
    ANDROID_VERSION_CODE = $${ARCSKY_ANDROID_BITNESS}$${ARCSKY_VER_MAJOR}$${ARCSKY_VER_MINOR}$${ARCSKY_ANDROID_PATCH}000
    ANDROID_VERSION_NAME = $${ARCSKY_VERSION}

    message(Arcsky Android versionCode $${ANDROID_VERSION_CODE} versionName $${ANDROID_VERSION_NAME})
}

# Branding

DEFINES += CUSTOMHEADER=\"\\\"HerelinkCorePlugin.h\\\"\"
DEFINES += CUSTOMCLASS=HerelinkCorePlugin

TARGET   = Herelink-QGroundControl
DEFINES += QGC_APPLICATION_NAME='"\\\"Arcsky Control\\\""'

DEFINES += QGC_ORG_NAME=\"\\\"Arcsky\\\"\"
DEFINES += QGC_ORG_DOMAIN=\"\\\"www.arcskytech.com\\\"\"

QGC_APP_NAME        = "Arcsky Control"
QGC_BINARY_NAME     = "Arcsky Control"
QGC_ORG_NAME        = "Arcsky"
QGC_ORG_DOMAIN      = "www.arcskytech.com"
QGC_ANDROID_PACKAGE = "arcsky.ArcskyControl"
QGC_APP_DESCRIPTION = "Arcsky Ground Control Station"
QGC_APP_COPYRIGHT   = "Copyright (C) 2024 Arcsky. All rights reserved."

# Remove code which the Herelink doesn't need
DEFINES += \
    QGC_GST_TAISYNC_DISABLED
    NO_SERIAL_LINK
    QGC_DISABLE_BLUETOOTH

# Enable Herelink AirUnit video config
DEFINES += \
    QGC_HERELINK_AIRUNIT_VIDEO

CONFIG += AndroidHomeApp

# Our own, custom resources
# Not yet used
#RESOURCES += \
#    $$PWD/custom.qrc

QML_IMPORT_PATH += \
   $$PWD/src

# Herelink specific custom sources
SOURCES += \
    $$PWD/src/HerelinkCorePlugin.cc \
    $$PWD/src/HerelinkOptions.cc \

HEADERS += \
    $$PWD/src/HerelinkCorePlugin.h \
    $$PWD/src/HerelinkOptions.h \

INCLUDEPATH += \
    $$PWD/src \

# Herelink specific custom sources, for HDMI switching
message("Including custom Herelink sources for source switching")

SOURCES += $$PWD/herelink/VideoStreamControl.cc
HEADERS += $$PWD/herelink/VideoStreamControl.h
INCLUDEPATH += $$PWD/herelink

# Custom versions of a Herelink build should only add changes below here to prevent conflicts
