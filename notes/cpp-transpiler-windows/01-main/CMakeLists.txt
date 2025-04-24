cmake_minimum_required(VERSION 3.10.0)
project(rdvcpp VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(3party)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_link_libraries (${PROJECT_NAME}
    cmdlime::cmdlime
    sfun::sfun
)
