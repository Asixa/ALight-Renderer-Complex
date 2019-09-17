#include "Scene.h"

ALightCreator::Scene::Scene()
{
}

void ALightCreator::Scene::AddObject(Object* object)
{
	objects.push_back(object);
}
