#include "Project.h"


void Project::Render()
{
	ImGui::Begin("Project", &enabled);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)

	ImGui::End();
}
