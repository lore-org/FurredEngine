#include <FurredEngine/window.h>

int main() {
    FE_Window* window = furred_window_create(&(FE_WindowSettings){
        854, 480,
        "FurredEngine Tests",
        NULL, // Stays as 3.2
        0 // Disables VSync
    });

    while (!glfwWindowShouldClose(window->glfw_window)) {
        glfwPollEvents();
        
        glfwSwapBuffers(window->glfw_window);
    }

    furred_window_destroy(window);
}