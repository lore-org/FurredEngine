#include <FurredEngine/window.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

FE_Window* furred_create_window(FE_WindowSettings* settings) {
    FE_WindowSettings* windowSettings = &(FE_WindowSettings){
        640, 480,
        "GLFW Window"
    };
    if (settings) {
        if (settings->width > 0) windowSettings->width = settings->width;
        if (settings->height > 0) windowSettings->height = settings->height;
        if (settings->title && strlen(settings->title) > 0) windowSettings->title = settings->title;
    }

    FE_Window* window = malloc(sizeof(FE_Window));
    assert(window && "Could not create window. Does the system have enough memory?");
    // Initialise GLFW
    assert(glfwInit() && "Could not initialise GLFW.");

    // Set requested OpenGL Context to 3.2
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    // Allow debugging of OpenGL
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    window->glfw_window = glfwCreateWindow(
        windowSettings->width, windowSettings->height,
        windowSettings->title,
        NULL, NULL);
    assert(window->glfw_window && "Could not create GLFW window.");

    // Switch OpenGL context to the current one
    glfwMakeContextCurrent(window->glfw_window);
    // Load OpenGL Addresses
    assert(gladLoadGL(glfwGetProcAddress) && "Could not load OpenGL.");
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