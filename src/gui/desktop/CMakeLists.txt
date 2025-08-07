cmake_minimum_required(VERSION 3.16)

project(brickgame VERSION 2.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

message(STATUS "Qt version: ${QT_VERSION_MAJOR}")

include_directories(
    ${CMAKE_SOURCE_DIR}/../../brick_game/snake
    ${CMAKE_SOURCE_DIR}/../../brick_game/tetris
)

set(PROJECT_SOURCES
        desktop.cc
        mainwindow.cc
        mainwindow.h
        gamefield.h
        gamefield.cc
        nextfield.h
        nextfield.cc
        stats.h 
        stats.cc
)

add_executable(snake_desktop
    ${PROJECT_SOURCES}
)
target_include_directories(snake_desktop PRIVATE
    ${CMAKE_SOURCE_DIR}/../../brick_game/snake
)
target_link_libraries(snake_desktop
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    ${CMAKE_SOURCE_DIR}/../../obj/snake/s21_snake.a
)

add_executable(tetris_desktop
    ${PROJECT_SOURCES}
)
target_include_directories(tetris_desktop PRIVATE
    ${CMAKE_SOURCE_DIR}/../../brick_game/tetris
)
target_link_libraries(tetris_desktop
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    ${CMAKE_SOURCE_DIR}/../../obj/tetris/s21_tetris.a
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.brickgame)
endif()
set_target_properties(tetris_desktop snake_desktop PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS tetris_desktop snake_desktop
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(tetris_desktop)
    qt_finalize_executable(snake_desktop)
endif()
