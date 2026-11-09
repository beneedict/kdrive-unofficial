# No-op sentry stub, see sentry.h in this directory.
#
# kDrive links against the sentry-native API.  This stub provides just
# enough of that API to build kDrive without sentry-native.  Every call
# is a no-op, nothing is reported and no network connection is opened.
#
# License: MIT

add_library(sentry_stub STATIC sentry.c)
set_target_properties(sentry_stub PROPERTIES
    OUTPUT_NAME sentry
    POSITION_INDEPENDENT_CODE ON
)
target_include_directories(sentry_stub PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
