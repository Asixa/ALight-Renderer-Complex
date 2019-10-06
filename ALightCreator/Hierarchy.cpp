#include "Hierarchy.h"
#include "Engine.h"
#include "Editor.h"
using namespace ALightCreator;

void Hierarchy::DrawTransform(Object* obj)
{
	if(obj->transform->children.size()==0)
	{
		ImGui::Selectable(obj->name.c_str(),false);
	}
	else
	{
		if (ImGui::TreeNode(obj->name.c_str()))
		{
			for (auto child : obj->transform->children)DrawTransform(child->object);
			ImGui::TreePop();
		}
	}
}

void Hierarchy::Render()
{
	ImGui::Begin("Hierarchy");                         
	
	for (auto obj : Engine::GetInstance().scene->objects)
	{
		DrawTransform(obj);
	}
	
	ImGui::End();
}


