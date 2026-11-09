# FindSentry.cmake - find the sentry API stub.
#
# kDrive links sentry::sentry and calls find_package(sentry REQUIRED).
# Fedora has no sentry-native; the kdrive-unofficial package provides a
# no-op stub that is added as a subdirectory before this module runs
# (see KDRIVE_SENTRY_STUB_DIR in the top-level CMakeLists.txt).
if(TARGET sentry_stub)
    if(NOT TARGET sentry::sentry)
        add_library(sentry::sentry ALIAS sentry_stub)
    endif()
    set(sentry_FOUND TRUE)
    set(SENTRY_FOUND TRUE)
    set(sentry_VERSION 0.0.0)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(sentry
    REQUIRED_VARS sentry_VERSION
)
