cmake_minimum_required(VERSION 2.8)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  # using Clang
  message("use clang")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
  # using GCC
  message("use gcc")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wnon-virtual-dtor")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
  # using Visual Studio C++
  message("use msvc")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
  #see parameter list here https://cmake.org/pipermail/cmake/2006-July/010189.html
endif()


if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fPIC -pthread")
endif(UNIX)

if(CYGWIN OR MINGW)
    string(REGEX REPLACE "-Wl,--out-implib,[^ ]+ " " " CMAKE_C_CREATE_SHARED_LIBRARY "${CMAKE_C_CREATE_SHARED_LIBRARY}")
    string(REGEX REPLACE "-Wl,--out-implib,[^ ]+ " " " CMAKE_CXX_CREATE_SHARED_LIBRARY "${CMAKE_CXX_CREATE_SHARED_LIBRARY}")
endif(CYGWIN OR MINGW)

project(DSPatch)

file(GLOB srcs src/*.cpp)
file(GLOB hdrs include/*.h)
file(GLOB in_hdrs include/dspatch/*.h)

include_directories(include)

# Build shared (LGPL)
add_library(
    ${PROJECT_NAME}
    ${srcs}
    ${hdrs}
    ${in_hdrs}
)

target_link_libraries(
    ${PROJECT_NAME}
    -static-libgcc
    -static-libstdc++
    gml_parser
)

# Link pthread and dl on Unix
if(UNIX)
    target_link_libraries(
        ${PROJECT_NAME}
        pthread
        dl
    )
endif(UNIX)

install(
    TARGETS ${PROJECT_NAME}
    DESTINATION lib
)

install(
    FILES ${hdrs}
    DESTINATION include
)

install(
    FILES ${in_hdrs}
    DESTINATION include/dspatch
)

option(BUILD_EXAMPLES "Build Examples" OFF)
option(BUILD_DOC "Build Documentation" OFF)

if(${BUILD_EXAMPLES})
    add_subdirectory(example)
    add_subdirectory(tutorial)
endif(${BUILD_EXAMPLES})

if(${BUILD_DOC})
    add_subdirectory(doc)
endif(${BUILD_DOC})
