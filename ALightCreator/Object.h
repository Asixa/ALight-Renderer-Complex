#pragma once
#include <vector>
#include "Component.h"
#include "Transform.h"
#include <string>
namespace ALightCreator {
	class Object
	{
	public:
		Object();
		std::string name = "Unnamed Object";
		Transform* transform;
		Component* AddComponent(Component* c);
		std::vector<Component*>components;
	};
}
