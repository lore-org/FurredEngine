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
 * @brief The settings to apply to the window on creation.
 * 
 * Any values left 0 or NULL should default to:
 * ```
 * {
 *     .width=640,
 *     .height=480,
 *     .title="GLFW Window"
 * }
 * ```
 */
typedef struct {
    /**
     * @brief The size of the window in pixels(?).
     * 
     */
    int width, height;
    /**
     * @brief The window's title.
     * 
     */
    const char* title;
} FE_WindowSettings;

/**
 * @brief Constructs a window using the applied `settings`.
 * 
 * @param settings A pointer to the settings to be applied. See @ref FE_WindowSettings.
 * @return FE_Window* 
 */
FE_EXPORT FE_Window* furred_create_window(FE_WindowSettings* settings);
/**
 * @brief Destroys a previously constructed window. See @ref furred_create_window.
 * 
 * @param window A pointer to the associated window.
 * @return void 
 */
FE_EXPORT void furred_destroy_window(FE_Window* window);