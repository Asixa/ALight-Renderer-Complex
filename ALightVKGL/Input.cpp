#include "Input.h"

void Input::Clear()
{
	MouseXoffset =0;
	MouseYoffset = 0;
}

void Input::UpdateMouse(double xpos, double ypos)
{
	if (!MouseReady)
	{
		lastX = xpos;
		lastY = ypos;
		MouseReady = true;
	}

	MouseXoffset = xpos - lastX;
	MouseYoffset =lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	
}

bool Input::KeyPress(int key)
{
	return glfwGetKey(window, key) == GLFW_PRESS;
}

bool Input::KeyDown(int key)
{
	return glfwGetKey(window, key) == GLFW_KEY_DOWN;
}

bool Input::KeyUp(int key)
{
	return glfwGetKey(window, key) == GLFW_RELEASE;
}
