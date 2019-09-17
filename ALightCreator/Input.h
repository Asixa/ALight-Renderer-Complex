#pragma once
#include "Application.h"

class  Input
{
public:
	static Input& GetInstance() { static Input instance; return instance; }
	GLFWwindow* window;
	bool MouseReady = false;
	float lastX = 0;
	float lastY = 0;
	float MouseXoffset, MouseYoffset, MouseScroll;

	void Clear();
	void UpdateMouse(double xpos, double ypos);
	bool KeyPress(int key);
	bool KeyDown(int key);
	bool KeyUp(int key);
};
