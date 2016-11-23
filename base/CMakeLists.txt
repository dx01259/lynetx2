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
        ThreadFactory.cpp
        TMap.cpp
        Mutex.cpp
        EpollObject.cpp
        MsgDeque.cpp)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(/usr/local/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

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
        ThreadFactory.h
        TMap.h
        Mutex.h
        EpollObject.h
        MsgDeque.h)