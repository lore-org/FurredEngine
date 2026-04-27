#include <FurredEngine/window.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

FE_Window* furred_window_create(FE_WindowSettings* settings) {
    FE_WindowSettings* windowSettings = &(FE_WindowSettings){
        .width = 640,
        .height = 480,
        .title = "GLFW Window",
        .gl_version = &FE_GL_32,
        .swap_interval = 1
    };
    if (settings) {
        #define SetIntSetting(setting) if (settings->setting > 0) windowSettings->setting = settings->setting
        
        SetIntSetting(width);
        SetIntSetting(height);

        if (settings->title && strlen(settings->title) > 0) windowSettings->title = settings->title;
        if (settings->gl_version) windowSettings->gl_version = settings->gl_version;
    }

    FE_Window* window = malloc(sizeof(FE_Window));
    assert(window && "Could not create window. Does the system have enough memory?");

    // Initialise GLFW
    assert(glfwInit() && "Could not initialise GLFW.");

    // Set OpenGL version settings
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Set requested OpenGL context to 3.2
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, windowSettings->gl_version->major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, windowSettings->gl_version->minor);

    // Allow debugging of OpenGL
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    window->glfw_window = glfwCreateWindow(
        windowSettings->width, windowSettings->height,
        windowSettings->title,
        NULL, NULL
    );
    assert(window->glfw_window && "Could not create GLFW window.");

    // Switch OpenGL context to the current one
    glfwMakeContextCurrent(window->glfw_window);

    // Load OpenGL Addresses
    assert(gladLoadGL(glfwGetProcAddress) && "Could not load OpenGL.");

    // Enable VSync
    glfwSwapInterval(windowSettings->swap_interval);

    // Enable transparency blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    window->glfw_window = window->glfw_window;
    return window;
}

void furred_window_destroy(FE_Window* window) {
    if (!window) return;

    glfwDestroyWindow(window->glfw_window);

    free(window);
    window = NULL;
}