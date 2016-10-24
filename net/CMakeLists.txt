SET(net_SRC
        AsyncSocket.cpp
        EpollService.cpp)

ADD_LIBRARY(net SHARED ${net_SRC})

SET(CMAKE_CXX_COMPILER "g++")

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/base)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/log)
INCLUDE_DIRECTORIES(/usr/local/include)

TARGET_LINK_LIBRARIES(net base)
TARGET_LINK_LIBRARIES(net log)

SET(HEADERS
        AsyncSocket.h
        EpollService.h)
