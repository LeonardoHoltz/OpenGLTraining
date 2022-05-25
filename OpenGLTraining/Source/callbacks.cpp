#include "../Headers/callbacks.h"

void Callbacks::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}