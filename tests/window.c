#include <FurredEngine/window.h>

int main() {
    FE_Window* window = furred_window_create(&(FE_WindowSettings){
        854, 480,
        "FurredEngine Tests",
        NULL, // Stays as 3.2
        0 // Disables VSync
    });

    while (!furred_window_check_and_update(window)) {
        // VSync buffer is swapped as soon as loop starts

        // If window is open, updates needed for frame are already polled
        // Otherwise the loop will exit early because furred_window_check_and_update returns 0

        // User runs code for this frame :3
    }

    furred_window_destroy(window);
}