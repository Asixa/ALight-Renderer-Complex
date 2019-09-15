#pragma once
#include "Scene.h"


class Engine
{
private:
	Engine();
public:
	void Start();
	void Update();
	static Engine& GetInstance();
	Scene* scene;
};
