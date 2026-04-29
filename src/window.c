#include "GLFW/glfw3.h"
#include <FurredEngine/window.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define __FE_WINDOW_EXISTS_ASSERT(w) \
    assert(w && "Window does not exist."); \
    assert(w->glfw_window && w->window_settings && "Window is not initialised.")

static FE_WindowSettings defaultWindowSettings = {
    .width = 640,
    .height = 480,
    .title = "GLFW Window",
    .gl_version = &FE_GL_32,
    .swap_interval = 1
};


FE_Window* furred_window_create(FE_WindowSettings* settings) {
    FE_WindowSettings* windowSettings = malloc(sizeof(FE_WindowSettings));
    assert(windowSettings && "Could not create window. Does the system have enough memory?");

    if (settings) {
        #define __FE_CopySetting(setting) windowSettings->setting = settings->setting
        #define __FE_CopyDefault(setting) windowSettings->setting = defaultWindowSettings.setting

        #define __FE_CheckConditionAndCopySetting(condition, setting) do { if (condition) (__FE_CopySetting(setting)); else (__FE_CopyDefault(setting)); } while (0)
        #define __FE_CheckValueAndCopySetting(setting) __FE_CheckConditionAndCopySetting(settings->setting >= 0, setting)
        
        __FE_CheckValueAndCopySetting(width);
        __FE_CheckValueAndCopySetting(height);
        __FE_CheckConditionAndCopySetting((settings->title && strlen(settings->title) > 0), title);
        __FE_CheckConditionAndCopySetting((settings->gl_version), gl_version);
        __FE_CheckValueAndCopySetting(swap_interval);
    }

    FE_Window* window = malloc(sizeof(FE_Window));
    assert(window && "Could not create window. Does the system have enough memory?");

    // Initialise GLFW
    assert(glfwInit() && "Could not initialise GLFW.");

    // Set OpenGL version settings
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    // Set requested OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, windowSettings->gl_version->major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, windowSettings->gl_version->minor);

    // Enable debugging of OpenGL
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

    // Set swapping interval
    glfwSwapInterval(windowSettings->swap_interval);

    // Enable transparency blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set engine window to GLFW user pointer
    glfwSetWindowUserPointer(window->glfw_window, window);

    // Copy FE_WindowSettings*
    window->window_settings = windowSettings;
    // Copy GLFWwindow*
    window->glfw_window = window->glfw_window;

    return window;
}

void furred_window_destroy(FE_Window* window) {
    if (!window) return;

    glfwDestroyWindow(window->glfw_window);
    free(window->window_settings);

    free(window);
    window = NULL;
}

// Wrapper around glfwSwapBuffers
void __furred_window_swap_buffers(FE_Window* window) {
    // TODO - run frame updates after user-defined logic is run
    __FE_WINDOW_EXISTS_ASSERT(window);

    // Wrapped function
    glfwSwapBuffers(window->glfw_window);
}

// Wrapper around glfwPollEvents
void __furred_window_poll_events(FE_Window* window) {
    // TODO - run frame updates before user-defined logic is run
    __FE_WINDOW_EXISTS_ASSERT(window);

    // Wrapped function
    glfwPollEvents();
}

int furred_window_check_and_update(FE_Window* window) {
    __FE_WINDOW_EXISTS_ASSERT(window);

    // Swap buffers for last processed frame
    __furred_window_swap_buffers(window);
    // Check if window should close before continuing
    if (!glfwWindowShouldClose(window->glfw_window)) return 0;
    // Poll events before processing of next frame starts
    __furred_window_poll_events(window);

    return 1;
}