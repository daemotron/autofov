cmake_minimum_required (VERSION 3.30)

# build universal 2 binary on macOS, supporting both, Intel Macs and Silicon (M1/M2)
if(APPLE)
    set (CMAKE_OSX_ARCHITECTURES "x86_64;arm64")
endif()

project (AutoFoV)
set(CMAKE_C_STANDARD 17)
add_compile_options(-Wall -Wunreachable-code -Wextra -Wshadow -Wfloat-equal -pedantic -fvisibility=hidden -fstack-protector -funwind-tables -fasynchronous-unwind-tables)

# Set the build type as a macro
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type (Debug, Release, RelWithDebInfo, MinSizeRel)" FORCE)
endif()
string(TOUPPER ${CMAKE_BUILD_TYPE} BUILD_TYPE_UPPER)

# Detect XPPL
get_filename_component(XPPL_PATH "./xppl/" ABSOLUTE)
message("-- Detecting XPPL path")

if(NOT EXISTS ${XPPL_PATH})
    message(FATAL_ERROR "Missing XPPL folder: ${XPPL_PATH}")
endif(NOT EXISTS ${XPPL_PATH})

# Embed SDK
include(cmake/download_sdk.cmake)

# Copy symbol collisions file
configure_file("src/collisions" "collisions" COPYONLY)

# Include files
include_directories ("${XPPL_PATH}/include")
include_directories ("${xpsdk_SOURCE_DIR}")
include_directories ("${xpsdk_SOURCE_DIR}/CHeaders/XPLM")
include_directories ("${xpsdk_SOURCE_DIR}/CHeaders/Wrappers")
include_directories ("${xpsdk_SOURCE_DIR}/CHeaders/Widgets")
include_directories ("${CMAKE_SOURCE_DIR}/src")

# Source files
file(GLOB_RECURSE AUTOFOV_SOURCES "${CMAKE_SOURCE_DIR}/src/*.c")
file(GLOB_RECURSE XPPL_COMMON_SOURCES "${XPPL_PATH}/xppl_common/*.c")
file(GLOB_RECURSE XPPL_CONFIG_SOURCES "${XPPL_PATH}/xppl_config/*.c")

set(
    SOURCES
    ${AUTOFOV_SOURCES}
    ${XPPL_COMMON_SOURCES} ${XPPL_CONFIG_SOURCES}
)

if(WIN32)
    link_directories("${xpsdk_SOURCE_DIR}/Libraries/Win")
    add_library(autofov SHARED ${SOURCES})
    target_compile_definitions(autofov PRIVATE XPLM200 IBM BUILD_TYPE_${BUILD_TYPE_UPPER})
    target_link_libraries(autofov XPLM_64 XPWidgets_64 -static-libgcc -static-libstdc++ -static ssp)
    set_target_properties(autofov PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/win_x64"
        OUTPUT_NAME "autofov"
        PREFIX ""
        SUFFIX ".xpl"
        LINK_FLAGS "-s -Wl,--version-script=collisions"
    )
endif()

if(LINUX)
    add_library(autofov SHARED ${SOURCES})
    target_compile_definitions(autofov PRIVATE XPLM200 LIN BUILD_TYPE_${BUILD_TYPE_UPPER})
    set_target_properties(autofov PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lin_x64"
        OUTPUT_NAME "autofov"
        PREFIX ""
        SUFFIX ".xpl"
        LINK_FLAGS "-s -Wl,--version-script=collisions"
    )
endif()

if(APPLE)
    link_directories("${xpsdk_SOURCE_DIR}/Libraries/Mac")
    add_library(autofov SHARED ${SOURCES})
    target_compile_definitions(autofov PRIVATE XPLM200 APL BUILD_TYPE_${BUILD_TYPE_UPPER})
    target_link_libraries(autofov "-framework XPLM_64" "-framework XPWidgets")
    set_target_properties(autofov PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/mac_x64"
        OUTPUT_NAME "autofov"
        PREFIX ""
        SUFFIX ".xpl"
        LINK_FLAGS "-s -Wl,--version-script=collisions"
    )
endif()
