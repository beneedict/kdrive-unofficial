# FindxxHash.cmake - find the xxHash library.
#
# Fedora's xxhash-devel ships only a pkg-config file, while kDrive calls
# find_package(xxHash) and links xxHash::xxhash.
find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
    pkg_check_modules(PC_XXHASH QUIET libxxhash)
endif()

find_path(XXHASH_INCLUDE_DIR
    NAMES xxhash.h
    HINTS ${PC_XXHASH_INCLUDE_DIRS}
)
find_library(XXHASH_LIBRARY
    NAMES xxhash
    HINTS ${PC_XXHASH_LIBRARY_DIRS}
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(xxHash
    REQUIRED_VARS XXHASH_LIBRARY XXHASH_INCLUDE_DIR
    VERSION_VAR PC_XXHASH_VERSION
)

if(xxHash_FOUND AND NOT TARGET xxHash::xxhash)
    add_library(xxHash::xxhash UNKNOWN IMPORTED)
    set_target_properties(xxHash::xxhash PROPERTIES
        IMPORTED_LOCATION "${XXHASH_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${XXHASH_INCLUDE_DIR}"
    )
endif()

mark_as_advanced(XXHASH_INCLUDE_DIR XXHASH_LIBRARY)
