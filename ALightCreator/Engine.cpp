#include "Engine.h"
#include "Camera.h"
#include "CameraMove.h"

Engine::Engine()
{
	scene = new Scene();
}

void Engine::Start()
{
	Camera::main = new Camera();
	auto camera_object = new Object();
	camera_object->AddComponent(Camera::main);
	scene->AddObject(camera_object);
	camera_object->name = "MainCamera";
	camera_object->transform->position = glm::vec3(0, 0, -3);

	auto cm = new CameraMove();
	camera_object->AddComponent(cm);
	cm->Init(glm::vec3(0.0f, 0.0f, 3.0f));
}

void Engine::Update()
{
	for (auto obj : scene->objects)
	{
		for (auto c : obj->components)c->Update();
	}
}

Engine& Engine::GetInstance(){static Engine instance;return instance;}
