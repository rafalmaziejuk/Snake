set(ENGINE_PRJ_NAME engine)
project(${ENGINE_PRJ_NAME})

add_library(${ENGINE_PRJ_NAME} "")
add_subdirectory(src)
target_link_libraries(${ENGINE_PRJ_NAME} PUBLIC ${LIBS_LIST})
target_include_directories(${ENGINE_PRJ_NAME} PUBLIC src)
