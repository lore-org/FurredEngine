#include "GLFW/glfw3.h"
#include <FurredEngine/window.h>
#include <stdlib.h>


FE_Window* furred_create_window() {
    FE_Window* window = malloc(sizeof(FE_Window));
    if (!window) return NULL;

    // Initialise GLFW
    if (!glfwInit()) return NULL;

    // Set requested OpenGL Context to 3.2
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    // Allow debugging of OpenGL
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    // TODO: Allow customisable window params
    window->glfw_window = glfwCreateWindow(640, 360, "", NULL, NULL);
    if (!window->glfw_window) return NULL;

    // Switch OpenGL context to the current one
    glfwMakeContextCurrent(window->glfw_window);
    // Load OpenGL Addresses
    if (!gladLoadGL(glfwGetProcAddress)) return NULL;
    // Enable VSync
    glfwSwapInterval(1);

    // Enable transparency blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Swap buffers once to update the screen
    glfwSwapBuffers(window->glfw_window);

    window->glfw_window = window->glfw_window;
    return window;
}

void furred_destroy_window(FE_Window* window) {
    if (!window) return;

    glfwDestroyWindow(window->glfw_window);

    free(window);
    window = NULL;
}