cmake_minimum_required(VERSION 2.6)

PROJECT(lynetx)

set(CMAKE_BUILD_TYPE "Debug")

set(CXX_FLAGS
        -g
        -O0
        # -DVALGRIND
        # -DMUDUO_STD_STRING
        -DCHECK_PTHREAD_RETURN_VALUE
        -D_FILE_OFFSET_BITS=64
        -Wall
        -Wextra
        -Wconversion
        -Wno-unused-parameter
        -Wold-style-cast
        -Woverloaded-virtual
        -Wpointer-arith
        -Wshadow
        -Wwrite-strings
        -march=native
        # -MMD
        #-std=c++0x
        -rdynamic
        )

set(CMAKE_CXX_COMPILER "g++")

set(CMAKE_MACOSX_RPATH 0)

set(CMAKE_CXX_FLAGS_DEBUG "-O0 ")
set(CMAKE_CXX_FLAGS_RELEASE "-fPIC -W -O2 -finline-limit=1000 -DNDEBUG")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lynetx/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lynetx/lib)

LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)
LINK_DIRECTORIES(/usr/local/lib)

add_subdirectory(base)
add_subdirectory(lib)
add_subdirectory(log)
add_subdirectory(net)

#暂时添加测试
set(mainSRC
        main.cpp)

add_executable(main ${mainSRC})