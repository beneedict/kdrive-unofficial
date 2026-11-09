# Findlog4cplus.cmake - find the log4cplus logging library.
#
# Fedora's log4cplus-devel ships only a pkg-config file and is built
# without UNICODE support, while kDrive logs wide strings.  The package
# therefore builds a private log4cplus with UNICODE=ON and points this
# module at it with KDRIVE_LOG4CPLUS_ROOT.
if(DEFINED KDRIVE_LOG4CPLUS_ROOT)
    list(PREPEND CMAKE_PREFIX_PATH "${KDRIVE_LOG4CPLUS_ROOT}")
    set(LOG4CPLUS_INCLUDE_DIR "${KDRIVE_LOG4CPLUS_ROOT}/include")
    find_library(LOG4CPLUS_LIBRARY
        NAMES log4cplus
        PATHS "${KDRIVE_LOG4CPLUS_ROOT}/lib" "${KDRIVE_LOG4CPLUS_ROOT}/lib64"
        NO_DEFAULT_PATH
    )
    set(LOG4CPLUS_VERSION 2.1.2)
else()
    find_package(PkgConfig QUIET)
    if(PkgConfig_FOUND)
        pkg_check_modules(PC_LOG4CPLUS QUIET log4cplus)
    endif()
    find_path(LOG4CPLUS_INCLUDE_DIR
        NAMES log4cplus/logger.h
        HINTS ${PC_LOG4CPLUS_INCLUDE_DIRS}
    )
    find_library(LOG4CPLUS_LIBRARY
        NAMES log4cplus
        HINTS ${PC_LOG4CPLUS_LIBRARY_DIRS}
    )
    set(LOG4CPLUS_VERSION ${PC_LOG4CPLUS_VERSION})
endif()

set(LOG4CPLUS_THREAD_POOL_ENABLED ON)
set(LOG4CPLUS_UNICODE_ENABLED ON)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(log4cplus
    REQUIRED_VARS LOG4CPLUS_LIBRARY LOG4CPLUS_INCLUDE_DIR
    VERSION_VAR LOG4CPLUS_VERSION
)

if(log4cplus_FOUND AND NOT TARGET log4cplus::log4cplus)
    add_library(log4cplus::log4cplus UNKNOWN IMPORTED)
    set_target_properties(log4cplus::log4cplus PROPERTIES
        IMPORTED_LOCATION "${LOG4CPLUS_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${LOG4CPLUS_INCLUDE_DIR}"
    )
endif()

mark_as_advanced(LOG4CPLUS_INCLUDE_DIR LOG4CPLUS_LIBRARY)
