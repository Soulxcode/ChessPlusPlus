cmake_minimum_required(VERSION 3.16)

project(ChessEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

add_executable(ChessEngine ${SOURCES})

if(WIN32)
    set_target_properties(ChessEngine PROPERTIES
        LINK_FLAGS "-mconsole"
    )
endif()