set(ENGINE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Engine.h
)

target_sources(${ENGINE_PRJ_NAME} PRIVATE ${ENGINE_SOURCES})
add_subdirectory(Engine)
