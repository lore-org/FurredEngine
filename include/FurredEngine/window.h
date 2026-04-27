#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "export.h"

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
} FE_Window;

/**
 * @brief A representation of an OpenGL version.
 * 
 */
typedef struct {
    int major;
    int minor;
} FE_GLVersion;

#define FE_GL_10 ((FE_GLVersion){1,0}) // OpenGL 1.0
#define FE_GL_11 ((FE_GLVersion){1,1}) // OpenGL 1.1
#define FE_GL_12 ((FE_GLVersion){1,2}) // OpenGL 1.2
#define FE_GL_13 ((FE_GLVersion){1,3}) // OpenGL 1.3
#define FE_GL_14 ((FE_GLVersion){1,4}) // OpenGL 1.4
#define FE_GL_15 ((FE_GLVersion){1,5}) // OpenGL 1.5

#define FE_GL_20 ((FE_GLVersion){2,0}) // OpenGL 2.0
#define FE_GL_21 ((FE_GLVersion){2,1}) // OpenGL 2.1

#define FE_GL_30 ((FE_GLVersion){3,0}) // OpenGL 3.0
#define FE_GL_31 ((FE_GLVersion){3,1}) // OpenGL 3.1
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
 * Any values left 0 or NULL should default to:
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
     * @brief The size of the window in screen coordinates. Usually measured in pixels, but may differ for retina displays.
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
     * 
     */
    int swap_interval;
} FE_WindowSettings;

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