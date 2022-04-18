set(SNAKE_PRJ_NAME snake)
project(${SNAKE_PRJ_NAME})

add_executable(${SNAKE_PRJ_NAME} "")
add_subdirectory(src)
target_link_libraries(${SNAKE_PRJ_NAME} PUBLIC engine)

add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_LIST_DIR}/copy_assets.cmake
)
add_dependencies(${SNAKE_PRJ_NAME} copy_assets)
