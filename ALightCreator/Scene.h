#pragma once
#include "imgui/imgui.h"
#include <glm/vec3.hpp>
#include "Object.h"


namespace ALightCreator {
	class Model;
	class Scene
	{
	public:
		std::vector<Object*>objects;
		Scene();
		void LoadScene();
		ImVec4 bgColor = ImVec4(0.2f, 0.2f, 0.2f, 1);
		int scene = 1;
		int LOD = 0;
		const char* path;
		glm::vec3 InitScale;
		glm::vec3 InitRotateAxis;
		glm::vec3 InitTranslation;
		float InitRotateDegree = 0;


		
		bool changed = false;
		Model* m;
		float objectMatrix[16] =
		{ 1.f, 0.f, 0.f, 0.f,
		  0.f, 1.f, 0.f, 0.f,
		  0.f, 0.f, 1.f, 0.f,
		  0.f, 0.f, 0.f, 1.f };


		void AddObject(Object* object);
	};
}
