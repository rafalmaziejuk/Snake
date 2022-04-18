cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)

project(snake_game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}")
    message(FATAL_ERROR
            "In-source builds are not permitted!\n"
            "Create separate build directory in repository's main directory.\n"
    )
endif()

add_subdirectory(third_party)
add_subdirectory(engine)
add_subdirectory(snake)

if (MSVC)
    set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT snake)
endif()
