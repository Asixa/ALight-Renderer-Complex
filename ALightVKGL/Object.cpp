#include "Object.h"
Object::Object()
{

	transform = new Transform();
	AddComponent(transform);
}

Component* Object::AddComponent(Component* c)
{
	c->object = this;
	c->transform = transform;
	components.push_back(c);
	return c;
}
