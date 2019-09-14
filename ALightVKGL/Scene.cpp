#include "Scene.h"

Scene::Scene()
{
	vertices = new float[12]{
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	indices = new unsigned[6]
	{
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
}
