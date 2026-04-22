#include <FurredEngine/vector.h>
#include <FurredEngine/window.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    FE_Window* window = furred_create_window(NULL);
    FE_Vector* vec = furred_vector_create(0, sizeof(float));

    float lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window->glfw_window)) {
        float nowTime = glfwGetTime();
        glfwPollEvents();

        float elapsed = nowTime - lastTime;

        furred_vector_push_back(vec, &elapsed);
        while (vec->size > 60) {
            furred_vector_erase(vec, 0);
        }

        float acc = 0;
        for (char i = 0; i < vec->size; i++) {
            float delta = *(float*)furred_vector_at(vec, i);
            acc += 1 / delta;
        }

        char title[30];
        snprintf(title, sizeof(title), "%f fps", acc / vec->size);
        glfwSetWindowTitle(window->glfw_window, title);
        
        lastTime = nowTime;
        glfwSwapBuffers(window->glfw_window);
    }

    furred_vector_destroy(vec);
    furred_destroy_window(window);
}