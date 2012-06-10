# set the version of cmake
cmake_minimum_required(VERSION 2.8)

# set the rootdir
set(ROOTDIR ${CMAKE_SOURCE_DIR})

# specify the cmake configuration file
include(cmake/config.cmake)

# set the directory build
include_directories(${ROOTDIR}/include)

# set the compilation options
add_definitions(-Wfatal-errors -std=c++0x -DZOOST_EXPORTS)

# add an option for choosing the build type (shared or static)
set(BUILD_SHARED_LIBS TRUE CACHE BOOL "TRUE to build SFML as shared libraries, FALSE to build it as static libraries")

# add an option for building the API documentation
set(BUILD_DOC FALSE CACHE BOOL "TRUE to generate the API documentation, FALSE to ignore it")

# add the source files
add_subdirectory(src)

install(
    DIRECTORY ./include/Zoost
    DESTINATION include
    COMPONENT devel
)