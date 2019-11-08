#include "Scene.h"
#include "Resource.h"
#include "Model.h"
ALightCreator::Scene::Scene()
{
	LOD = 0;
	LoadScene();
	
}

void ALightCreator::Scene::LoadScene()
{
	switch (scene)
	{

	case 1:
	{
		path = "../Resources/Objects/dae/cube.dae";
		InitTranslation = glm::vec3(0.0f, 0.0f, 0.0f);
		InitScale = glm::vec3(1, 1, 1);
		InitRotateDegree = 0;
		InitRotateAxis = glm::vec3(1, 0, 0);
		break;
	}
	case 2: {
		path = "../Resources/Objects/dae/bunny.dae";
		InitTranslation = glm::vec3(0.0f, -0.75f, 0.0f);
		InitScale = glm::vec3(0.02f, 0.02f, 0.02f);
		InitRotateDegree = -90.0f / 57.2958f;
		InitRotateAxis = glm::vec3(1, 0, 0);
		break;
	}
	case 3:
	{
		path = "../Resources/Objects/dae/monkey.dae";
		InitTranslation = glm::vec3(0.0f, 0.0f, 0.0f);
		InitScale = glm::vec3(1, 1, 1);
		InitRotateDegree = -90.0f / 57.2958f;
		InitRotateAxis = glm::vec3(1, 0, 0);
		break;
	}
	}
	free(m);
	m = new Model(path);
}

void ALightCreator::Scene::AddObject(Object* object)
{

	objects.push_back(object);
}
