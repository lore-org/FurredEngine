#include <FurredEngine/window.h>

int main() {
    FE_Window* window = furred_create_window(NULL);

    while (!glfwWindowShouldClose(window->glfw_window)) {
        glfwPollEvents();
        
        glfwSwapBuffers(window->glfw_window);
    }

    furred_destroy_window(window);
}