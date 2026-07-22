cmake_minimum_required(VERSION 3.16)

project(ChessEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

add_executable(ChessEngine ${SOURCES})

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

target_link_libraries(ChessEngine
    SFML::Graphics
    SFML::Window
    SFML::System
)