#pragma once
#include "Component.h"
#include "glm/vec3.hpp"

class Transform:public Component
{
public:
	glm::vec3 position;
	glm::vec3 rotation; 
	glm::vec3 scale;
};

