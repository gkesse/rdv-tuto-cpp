cmake_minimum_required(VERSION 3.10.0)
project(rdvcpp VERSION 0.1.0 LANGUAGES C CXX)

add_executable(rdvcpp
    main.cpp
    cClient.cpp
    cClientInit.cpp
    cClientSocket.cpp
    cErrorMsg.cpp
)

target_link_libraries(${PROJECT_NAME}
    ws2_32
)
