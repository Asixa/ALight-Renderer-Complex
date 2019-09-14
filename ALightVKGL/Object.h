#pragma once
#include <vector>
#include "Component.h"
#include "Transform.h"

class Object
{
public:
	Transform* transform;
	Component* AddComponent();
private:
	std::vector<Component*>components;
};
