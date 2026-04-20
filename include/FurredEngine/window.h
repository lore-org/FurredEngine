#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "exports.h"

typedef struct {
    GLFWwindow* glfw_window;
} FE_Window;

typedef struct {
    int width;
    int height;
    const char* title;
} FE_WindowSettings;

// If invalid, window settings default to { .width=640, .height=480, .title="GLFW Window" }
FE_EXPORT FE_Window* furred_create_window(FE_WindowSettings* settings);
FE_EXPORT void furred_destroy_window(FE_Window* window);