#include "../Headers/callbacks.h"

void Callbacks::SetupCallbackCameraPointer(Camera& cam) {
    camera = cam;
}


Callbacks::Callbacks(Window& window, Camera& new_camera) : camera(new_camera) {
    // Define GLFW callbacks for user input.
    glfwSetFramebufferSizeCallback(window.window_, Callbacks::FramebufferSizeCallback);
}

void Callbacks::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Callbacks::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

}