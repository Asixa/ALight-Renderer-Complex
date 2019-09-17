#pragma once
#include "imgui/imgui.h"
#include <glm/vec3.hpp>
#include "Object.h"
namespace ALightCreator {
	class Scene
	{
	public:
		std::vector<Object*>objects;
		Scene();
		ImVec4 bgColor = ImVec4(0.2f, 0.2f, 0.2f, 1);
		float vertices[180] = {
		  -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		   0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		  -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		   0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		   0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		   0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		  -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		  -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		  -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		  -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		   0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		   0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		   0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		   0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		   0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		   0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		  -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};
		unsigned int* indices = new unsigned[6]
		{
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};
		float objectMatrix[16] =
		{ 1.f, 0.f, 0.f, 0.f,
		  0.f, 1.f, 0.f, 0.f,
		  0.f, 0.f, 1.f, 0.f,
		  0.f, 0.f, 0.f, 1.f };


		void AddObject(Object* object);
	};
}