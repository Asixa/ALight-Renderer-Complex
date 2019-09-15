#include "Scene.h"

Scene::Scene()
{
	// vertices = new float[12]{
	// 	 0.5f,  0.5f, 0.0f,  // top right
	// 	 0.5f, -0.5f, 0.0f,  // bottom right
	// 	-0.5f, -0.5f, 0.0f,  // bottom left
	// 	-0.5f,  0.5f, 0.0f   // top left 
	// };
	
}

void Scene::AddObject(Object* object)
{
	objects.push_back(object);
}
