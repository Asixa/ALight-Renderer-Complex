#pragma once

#include "Component.h"
#include <glm/mat4x4.hpp>
namespace ALightCreator {
	class Camera :public Component
	{
	public:
		float FOV = 45.0f;
		float near = 0.1f, far = 100.0f;
		int width = 800, height = 600;

		glm::mat4 view, projection;
		static Camera* main;
		void Update()override;
		Camera();
	};
}