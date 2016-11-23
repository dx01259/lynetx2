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

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-fPIC -W -O2 -finline-limit=1000 -DNDEBUG")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall") 

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lynetx/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lynetx/lib)

LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)
LINK_DIRECTORIES(/usr/local/lib)

add_subdirectory(base)
add_subdirectory(lib)
add_subdirectory(log)
add_subdirectory(net)
add_subdirectory(test)

set(CMAKE_INSTALL_RPATH ${PROJECT_SOURCE_DIR}/cmake/lynetx/install)

install(TARGETS
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
