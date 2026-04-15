include(CPM)
include(CheckIncludeFile)

check_include_file("X11/X.h" HAS_X11)
if (HAS_X11)
    set(GLAD_GLX "glx=1.4")
endif()

CPMAddPackage(
    NAME glad
    VERSION 2.0.8
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v2.0.8
)

include("${glad_SOURCE_DIR}/cmake/CMakeLists.txt")
glad_add_library(
    glad_loader
    API
        "${GLAD_GLX}"
        "gl:core=3.2"
)

target_link_libraries(FurredEngine PUBLIC glad_loader)