cmake_minimum_required(VERSION 3.10.0)
project(rdvcpp VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

add_executable(rdvcpp
    main.cpp
    cClient.cpp
    cClientInit.cpp
    cClientSocket.cpp
    cFile.cpp
    cFTP.cpp
    cString.cpp
    cErrorMsg.cpp
)

target_link_libraries(${PROJECT_NAME}
    ws2_32
)
