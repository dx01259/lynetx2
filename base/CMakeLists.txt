SET(base_SRC
        Socket.cpp
        BaseException.cpp
        BServerPkg.cpp
        UtilXml.cpp
        ThreadPool.cpp
        BaseFunc.cpp
        BaseTime.cpp
        Object.cpp
        Timeout.cpp
        ThreadFactory.cpp TMap.cpp TMap.h Mutex.cpp Mutex.h)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/open/tinyxml2-4.0.1)
INCLUDE_DIRECTORIES(/usr/local/include)

SET(CMAKE_CXX_COMPILER "g++")
ADD_LIBRARY(base SHARED ${base_SRC})
TARGET_LINK_LIBRARIES(base tinyxml2)

SET(HEADERS
        Socket.h
        BaseException.h
        BServerPkg.h
        config.h
        UtilXml.h
        ThreadPool.h
        BaseFunc.h
        BaseTime.h
        Object.h
        define.h
        Timeout.h
        ThreadFactory.h)