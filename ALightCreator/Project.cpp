#include "Project.h"
#include "Engine.h"
using namespace ALightCreator;

void Project::Render()
{
	ImGui::Begin("Project", &enabled);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
	ImGui::Columns(2, "word-wrapping");
	//ImGui::Separator();
	ImGui::TextWrapped("The quick brown fox jumps over the lazy dog.");
	ImGui::TextWrapped("Hello Left");
	ImGui::NextColumn();
	ImGui::TextWrapped("The quick brown fox jumps over the lazy dog.");
	ImGui::TextWrapped("Hello Right");
	ImGui::Columns(1);
	//ImGui::Separator();
	ImGui::End();
}
