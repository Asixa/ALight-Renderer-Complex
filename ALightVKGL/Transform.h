#pragma once
#include "Component.h"
#include "glm/vec3.hpp"
#include "glm/gtc/quaternion.hpp"
class Transform:public Component
{

public:
	glm::vec3 position;
	// glm::qua<float,>rotation;
};
