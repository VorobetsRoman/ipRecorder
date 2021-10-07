cmake_minimum_required(VERSION 3.5)

project(ipRecorder VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Network REQUIRED)

set(PROJECT_SOURCES
        src/main.cpp
        src/iprecorderwgt.cpp src/iprecorderwgt.h src/iprecorderwgt.ui
        src/playerform.cpp src/playerform.h src/playerform.ui
        src/recorderform.cpp src/recorderform.h src/recorderform.ui
        src/splitform.cpp src/splitform.h src/splitform.ui
        src/Common/peer.h src/Common/peer.cpp
        src/Common/socketpeer.h src/Common/socketpeer.cpp
        src/Common/serverpeer.h src/Common/serverpeer.cpp
        src/Common/usersettings.h src/Common/usersettings.cpp
        res/buttons.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ipRecorder
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ipRecorder APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(ipRecorder SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ipRecorder
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(ipRecorder PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
    )


if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ipRecorder)
endif()
