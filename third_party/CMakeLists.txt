set(LIBS_FOLDER "third_party")

# freetype
add_subdirectory(freetype)
set_target_properties(
    freetype
    PROPERTIES FOLDER "${LIBS_FOLDER}"
)

# glad
add_subdirectory(glad)
set_target_properties(
    glad
    PROPERTIES FOLDER "${LIBS_FOLDER}"
)

# glfw
set(GLFW_BUILD_EXAMPLES  OFF CACHE INTERNAL "")
set(GLFW_BUILD_TESTS     OFF CACHE INTERNAL "")
set(GLFW_BUILD_DOCS      OFF CACHE INTERNAL "")
set(GLFW_INSTALL         OFF CACHE INTERNAL "")
add_subdirectory(glfw)
set_target_properties(
    glfw
    update_mappings
    PROPERTIES FOLDER "${LIBS_FOLDER}/glfw"
)

# glm
set(GLM_TEST_ENABLE      OFF CACHE INTERNAL "")
add_subdirectory(glm)
set_target_properties(
    glm
    uninstall
    PROPERTIES FOLDER "${LIBS_FOLDER}/glm"
)

# imgui
add_subdirectory(imgui)
set_target_properties(
    imgui
    PROPERTIES FOLDER "${LIBS_FOLDER}"
)

# stb_image
add_subdirectory(stb_image)
set_target_properties(
    stb_image
    PROPERTIES FOLDER "${LIBS_FOLDER}"
)

set(LIBS_LIST 
    freetype
    glad
    glfw
    glm
    imgui
    stb_image
    CACHE INTERNAL ""
)
