include(CPM)

CPMAddPackage(
    NAME GLFW
    VERSION 3.4
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
    OPTIONS
        "GLFW_BUILD_DOCS OFF"
        "GLFW_BUILD_X11 ON"
        "GLFW_BUILD_WAYLAND OFF"
)

target_link_libraries(FurredEngine PUBLIC glfw)