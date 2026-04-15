#pragma once

#include "gl.h"
#include "exports.h"

typedef struct FE_Window FE_Window;
struct FE_Window {
    GLFWwindow* glfw_window;
};

FE_EXPORT FE_Window* furred_create_window();
FE_EXPORT void furred_destroy_window(FE_Window* window);