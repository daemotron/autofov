cmake_minimum_required (VERSION 3.2)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

# build universal 2 binary on macOS, supporting both, Intel Macs and Silicon (M1/M2)
if(APPLE)
    set (CMAKE_OSX_ARCHITECTURES "x86_64;arm64")
endif()

project (AutoFoV)

# For CMake versions < 3.25
if(CMAKE_VERSION VERSION_LESS "3.25")
    if(UNIX AND NOT APPLE)
        set(LINUX TRUE)
        message("-- Linux detected")
    endif()
endif()

# Detect SDK
get_filename_component(SDK_PATH "./SDK/" ABSOLUTE)
message("-- Detecting X-Plane SDK path")

if(NOT EXISTS ${SDK_PATH})
    message(FATAL_ERROR "Missing SDK folder: ${SDK_PATH}")
endif(NOT EXISTS ${SDK_PATH})

# Detect XPPL
get_filename_component(XPPL_PATH "./xppl/" ABSOLUTE)
message("-- Detecting XPPL path")

if(NOT EXISTS ${XPPL_PATH})
    message(FATAL_ERROR "Missing XPPL folder: ${XPPL_PATH}")
endif(NOT EXISTS ${XPPL_PATH})

# Copy symbol collisions file
configure_file("src/collisions" "collisions" COPYONLY)

# Global compiler flags
set (GCC_DEFAULT_FLAGS -std=gnu17 -Wall -Wunreachable-code -pipe -Wextra -Wshadow -Wfloat-equal -pedantic -fvisibility=hidden -O2 -fmessage-length=0 -D_FORTIFY_SOURCE=2 -fstack-protector -funwind-tables -fasynchronous-unwind-tables -W -DXPLM200 -DXPLM210 -DXPLM300)
set (GXX_DEFAULT_FLAGS -std=gnu++17 -Wall -Wunreachable-code -pipe -Wextra -Wshadow -Wfloat-equal -pedantic -fvisibility=hidden -O2 -fmessage-length=0 -D_FORTIFY_SOURCE=2 -fstack-protector -funwind-tables -fasynchronous-unwind-tables -W -DXPLM200 -DXPLM210 -DXPLM300)

# Include files
include_directories ("./src")
include_directories ("${SDK_PATH}")
include_directories ("${SDK_PATH}/CHeaders/XPLM")
include_directories ("${SDK_PATH}/CHeaders/Wrappers")
include_directories ("${SDK_PATH}/CHeaders/Widgets")
include_directories ("${XPPL_PATH}/include")

file(GLOB_RECURSE AUTOFOV_SOURCES "src/*.c")
file(GLOB_RECURSE XPPL_COMMON_SOURCES "xppl/xppl_common/*.c")
file(GLOB_RECURSE XPPL_CONFIG_SOURCES "xppl/xppl_config/*.c")

set(SOURCES ${AUTOFOV_SOURCES} ${XPPL_COMMON_SOURCES} ${XPPL_CONFIG_SOURCES})

if(WIN32)
    cmake_policy(SET CMP0015 NEW)
    set (CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
    set (CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
    link_directories("${SDK_PATH}/Libraries/Win")
    add_library(WIN_RELEASE_64 SHARED ${SOURCES})
    target_compile_options(WIN_RELEASE_64 PRIVATE ${GCC_DEFAULT_FLAGS} -s -c -fno-stack-protector -static-libgcc -static-libstdc++ -DXPLM200 -DIBM)
    target_link_libraries(WIN_RELEASE_64 XPLM_64 XPWidgets_64 -static-libgcc -static-libstdc++ -static ssp)
    set_target_properties(WIN_RELEASE_64 PROPERTIES LINK_FLAGS "-s -Wl,--version-script=collisions")
    set_target_properties(WIN_RELEASE_64 PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/AutoFoV/win_x64/")
    set_target_properties(WIN_RELEASE_64 PROPERTIES OUTPUT_NAME "AutoFoV.xpl")
    set_target_properties(WIN_RELEASE_64 PROPERTIES PREFIX "")
    set_target_properties(WIN_RELEASE_64 PROPERTIES SUFFIX "")
endif()

if(LINUX)
    add_library(LIN_RELEASE_64 SHARED ${SOURCES})
    target_compile_options(LIN_RELEASE_64 PRIVATE ${GCC_DEFAULT_FLAGS} -m64 -fPIC -DLIN)
    set_target_properties(LIN_RELEASE_64 PROPERTIES LINK_FLAGS "-Wl,--version-script=collisions")
    set_target_properties(LIN_RELEASE_64 PROPERTIES PREFIX "")
    set_target_properties(LIN_RELEASE_64 PROPERTIES SUFFIX "")
    set_target_properties(LIN_RELEASE_64 PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/AutoFoV/lin_x64/")
    set_target_properties(LIN_RELEASE_64 PROPERTIES OUTPUT_NAME "AutoFoV.xpl")
endif()

if(APPLE)
    cmake_policy(SET CMP0042 NEW)
    set (CMAKE_SYSTEM_NAME Darwin)
    set (CMAKE_CXX_COMPILER g++)
    set (CMAKE_OSX_ARCHITECTURES "x86_64;arm64")
    add_library(MAC_RELEASE_64 SHARED ${SOURCES})
    target_compile_options(MAC_RELEASE_64 PRIVATE ${GCC_DEFAULT_FLAGS} -nostdinc++ -I/Library/Developer/CommandLineTools/usr/include/c++/v1 -DXPLM200 -DAPL)
    target_link_libraries(MAC_RELEASE_64 "-F${SDK_PATH}/Libraries/Mac" "-framework XPLM" "-framework XPWidgets" "-framework OpenGL" "-nodefaultlibs" "-lc++" "-lc++abi" "-lm" "-lc")
    set_target_properties(MAC_RELEASE_64 PROPERTIES LINK_FLAGS "-m64 -fvisibility=hidden")
    set_target_properties(MAC_RELEASE_64 PROPERTIES PREFIX "")
    set_target_properties(MAC_RELEASE_64 PROPERTIES SUFFIX "")
    set_target_properties(MAC_RELEASE_64 PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/AutoFoV/mac_x64/")
    set_target_properties(MAC_RELEASE_64 PROPERTIES OUTPUT_NAME "AutoFoV.xpl")
endif()
