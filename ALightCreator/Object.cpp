#include "Object.h"
using namespace  ALightCreator;
ALightCreator::Object::Object()
{

	transform = new Transform();
	AddComponent(transform);
}

Component* ALightCreator::Object::AddComponent(Component* c)
{
	c->object = this;
	c->transform = transform;
	components.push_back(c);
	return c;
}
