#include <FurredEngine/vector.h>
#include <FurredEngine/window.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    FE_Window* window = furred_window_create(NULL);
    FE_Vector* vec = furred_vector_create(0, sizeof(float));

    float lastTime = glfwGetTime();
    while (!furred_window_check_and_update(window)) {
        float nowTime = glfwGetTime();

        float elapsed = nowTime - lastTime;

        furred_vector_push_back(vec, &elapsed);
        while (vec->size > 10) {
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
    }

    furred_vector_destroy(vec);
    furred_window_destroy(window);
}