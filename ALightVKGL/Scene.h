#pragma once
#include "imgui/imgui.h"

class Scene
{
public:
	Scene();
	ImVec4 bgColor;
	float* vertices;
	unsigned int* indices;
};
