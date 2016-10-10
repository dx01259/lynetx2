SET(base_SRC
        Socket.cpp
        BaseException.cpp
        BServerPkg.cpp
        UtilXml.cpp)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/open/tinyxml2-4.0.1)

SET(CMAKE_CXX_COMPILER "g++")
ADD_LIBRARY(base SHARED ${base_SRC})
TARGET_LINK_LIBRARIES(base tinyxml2)

SET(HEADERS
        Socket.h
        BaseException.h
        BServerPkg.h
        config.h
        UtilXml.h
        )