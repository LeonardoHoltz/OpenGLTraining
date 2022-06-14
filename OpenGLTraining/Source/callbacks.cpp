#include "../Headers/callbacks.h"

void Callbacks::SetupCallbackCameraPointer(Camera& cam) {
    camera = cam;
}


Callbacks::Callbacks(Window& window, Camera& new_camera) : camera(new_camera) {
    glfwSetWindowUserPointer(window.window_, this);

    // This is needed to allow the use of class members of the callbacks class in the GLFW callback functions, such as the camera member.
    GLFWkeyfun KeyCallback = [](GLFWwindow* local_window, int key, int scancode, int action, int mods) {

        Callbacks* callback = static_cast<Callbacks*>(glfwGetWindowUserPointer(local_window));
        callback->KeyCallback(local_window, key, scancode, action, mods);
    };

    // Define GLFW callbacks for user input.
    glfwSetFramebufferSizeCallback(window.window_, Callbacks::FramebufferSizeCallback);
    glfwSetKeyCallback(window.window_, KeyCallback);
}

void Callbacks::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Callbacks::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

}