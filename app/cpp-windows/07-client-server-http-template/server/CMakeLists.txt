cmake_minimum_required(VERSION 3.10.0)
project(rdvcpp VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}
    main.cpp
    cServer.cpp
    cServerInit.cpp
    cServerSocket.cpp
    cServerClient.cpp
    cServerApp.cpp
    cHTTP.cpp
    cHttpApp.cpp
    cHttpGet.cpp
    cHttpStatusCode.cpp
    cMimeType.cpp
    cErrorMsg.cpp
    cString.cpp
    cFile.cpp
)

target_link_libraries(${PROJECT_NAME}
    ws2_32
)
