cmake_minimum_required(VERSION 3.10.0)
project(rdvcpp VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_PREFIX_PATH "C:/tools/Qt/6.9.0/msvc2022_64/lib/cmake")

find_package(Qt6 REQUIRED COMPONENTS
    Widgets
    SerialPort
)

qt_wrap_ui(UI_FILES
    cMainWindow.ui
    cPortAction.ui
    cMessageSend.ui
    cMessageRecv.ui
)

add_executable(rdvcpp
    main.cpp
    cMainWindow.cpp
    cPortAction.cpp
    cMessageSend.cpp
    cMessageRecv.cpp
    resources.qrc
    ${UI_FILES}
)

target_link_libraries (rdvcpp
    Qt6::Widgets
    Qt6::SerialPort
)
