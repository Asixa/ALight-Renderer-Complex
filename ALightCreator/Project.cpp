#include "Project.h"
#include "Engine.h"
using namespace ALightCreator;

void Project::Render()
{
	ImGui::Begin("Project", &enabled);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)

	ImGui::End();
}
