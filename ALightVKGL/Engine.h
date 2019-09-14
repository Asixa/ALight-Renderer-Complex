#pragma once
#include "Scene.h"


class Engine
{
private:
	Engine();
public:
	
	static Engine& GetInstance();
	Scene* scene;
};
