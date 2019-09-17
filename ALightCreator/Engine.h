#pragma once
#include "Scene.h"

namespace ALightCreator {
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
}
