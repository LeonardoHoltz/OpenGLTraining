// callbacks.h

#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <GLFW/glfw3.h>
#include "window.h"
#include "camera.h"

class Callbacks {
private:
	Camera& camera;
public:
	Callbacks(Window& window, Camera& new_camera);
	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	void SetupCallbackCameraPointer(Camera&);
};

#endif // CALLBACKS_H
