set(TcpService_SRC
        TcpService.cpp
        TcpServiceMain.cpp)

set(TcpClient_SRC
        TcpClient.cpp)

set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_CXX_COMPILER "g++")

include_directories(${PROJECT_SOURCE_DIR}/base)
include_directories(${PROJECT_SOURCE_DIR}/log)
include_directories(${PROJECT_SOURCE_DIR}/net)
include_directories(/usr/local/include)
link_directories(${PROJECT_SOURCE_DIR}/cmake/lynetx/lib)

add_executable(TcpService ${TcpService_SRC})
add_executable(TcpClient ${TcpClient_SRC})

target_link_libraries(TcpService base)
target_link_libraries(TcpService net)
target_link_libraries(TcpService log)

target_link_libraries(TcpClient base)
target_link_libraries(TcpClient net)
target_link_libraries(TcpClient log)

set(HEADERS
        TcpService.h
        TcpClient.h)

