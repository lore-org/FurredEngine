#include <FurredEngine/window.h>

int main() {
    FE_Window* window = furred_window_create(NULL);

    while (!glfwWindowShouldClose(window->glfw_window)) {
        glfwPollEvents();
        
        glfwSwapBuffers(window->glfw_window);
    }

    furred_window_destroy(window);
}