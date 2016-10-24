SET(log_SRC
        LoggerManager.cpp
        Logger.cpp)

SET(CMAKE_CXX_COMPILER "g++")
ADD_LIBRARY(log SHARED ${log_SRC})

SET(HEADERS
        LoggerManager.h
        Logger.h)