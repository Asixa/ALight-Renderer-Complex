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
		static Engine& GetInstance() { static Engine instance; return instance; }
		Scene* scene;
	};
}
