cmake_minimum_required(VERSION 3.16)

project(Chess++)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

add_executable(ChessGame ${SOURCES})

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

target_include_directories(ChessGame PRIVATE
    include
    include/pieces
    include/ui
)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

target_link_libraries(ChessGame
    SFML::Graphics
    SFML::Window
    SFML::System
)