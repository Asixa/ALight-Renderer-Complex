#pragma once
#include "Component.h"
#include "glm/vec3.hpp"
#include <vector>

namespace ALightCreator {
	class Transform :public Component
	{
	public:
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		glm::vec3 Front, Right, Up;
		Transform* parent;
		std::vector<Transform*>children;
		void Update() override;
		void SetParent(Transform* t);
	};
}
