#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "export.h"

/**
 * @brief A representation of an OpenGL version.
 * 
 */
typedef struct {
    int major;
    int minor;
} FE_GLVersion;

#define FE_GL_32 ((FE_GLVersion){3,2}) // OpenGL 3.2
#define FE_GL_33 ((FE_GLVersion){3,3}) // OpenGL 3.3

#define FE_GL_40 ((FE_GLVersion){4,0}) // OpenGL 4.0
#define FE_GL_41 ((FE_GLVersion){4,1}) // OpenGL 4.1
#define FE_GL_42 ((FE_GLVersion){4,2}) // OpenGL 4.2
#define FE_GL_43 ((FE_GLVersion){4,3}) // OpenGL 4.3
#define FE_GL_44 ((FE_GLVersion){4,4}) // OpenGL 4.4
#define FE_GL_45 ((FE_GLVersion){4,5}) // OpenGL 4.5
#define FE_GL_46 ((FE_GLVersion){4,6}) // OpenGL 4.6

/**
 * @brief The settings to apply to the window on creation.
 * 
 * Any values left -1 or NULL will default to:
 * ```
 * {
 *     .width = 640,
 *     .height = 480,
 *     .title = "GLFW Window",
 *     .gl_version = &FE_GL_32,
 *     .swap_interval = 1
 * }
 * ```
 */
typedef struct {
    /**
     * @brief The size of the window in screen coordinates. Measured in logical pixels.
     * 
     */
    int width, height;
    /**
     * @brief The window's title, encoded in UTF-8.
     * 
     */
    const char* title;
    /**
     * @brief The target OpenGL version to run.
     * 
     */
    FE_GLVersion* gl_version;
    /**
     * @brief How many screen updates to wait before updating the display buffer. Also known as VSync.
     * @warning Versions below OpenGL 3.2 may cause issues.
     */
    int swap_interval;
    
} FE_WindowSettings;

/**
 * @brief A physical window on the desktop.
 * 
 */
typedef struct {
    /**
     * @brief A GLFW window object.
     * 
     */
    GLFWwindow* glfw_window;
    /**
     * @brief The settings used to create the window.
     * 
     */
    FE_WindowSettings* window_settings;
} FE_Window;

/**
 * @brief Constructs a window using the applied `settings`.
 * 
 * @param settings A pointer to the settings to be applied. See @ref FE_WindowSettings.
 * @return FE_Window*
 */
FE_EXPORT FE_Window* furred_window_create(FE_WindowSettings* settings);
/**
 * @brief Destroys a previously constructed window. See @ref furred_window_create.
 * 
 * @param window A pointer to the associated window.
 * @return void 
 */
FE_EXPORT void furred_window_destroy(FE_Window* window);

/**
 * @brief Handles per-frame updates, and returns whether the window should close.
 * 
 * ```c
 * FE_Window* someWindow = ...;
 * 
 * // This loop runs until window should close (@see glfwWindowShouldClose)
 * while (!furred_window_check_and_update(someWindow)) {
 *     // Inside of `furred_window_check_and_update`:
 *         // The window's back buffer is swapped to the front buffer. (@see glfwSwapBuffers)
 *         // Then, the status of the window is checked to make sure it does not need to be closed. (@see glfwWindowShouldClose)
 *         // Finally, events such as keypresses and mouse movements are polled. (@see glfwPollEvents)
 * 
 *     // Afterwards, the user-defined code is allowed to run.
 * 
 *     // Because the buffers are swapped at the beginning of each loop instead of the end,
 *     // the very first frame will be displayed as a blank screen.
 *     // If this is undesireable, you can make the required glfw calls yourself.
 * }
 * ```
 * 
 * @param window A pointer to the associated window.
 * @return int Whether the current window should close. @see glfwWindowShouldClose.
 */
FE_EXPORT int furred_window_check_and_update(FE_Window* window);