#include "Property.h"
#include "Engine.h"


void Property::Render()
{
	ImGui::Begin("Property", &enabled);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::ColorEdit3("Background color", (float*) & (Engine::GetInstance().scene->bgColor)); // Edit 3 floats representing a color
	if (ImGui::CollapsingHeader("Help"))
	{
		ImGui::Text("PROGRAMMER GUIDE:");
		ImGui::BulletText("Please see the ShowDemoWindow() code in imgui_demo.cpp. <- you are here!");
		ImGui::BulletText("Please see the comments in imgui.cpp.");
		ImGui::BulletText("Please see the examples/ in application.");
		ImGui::BulletText("Enable 'io.ConfigFlags |= NavEnableKeyboard' for keyboard controls.");
		ImGui::BulletText("Enable 'io.ConfigFlags |= NavEnableGamepad' for gamepad controls.");
		ImGui::Separator();

		ImGui::Text("USER GUIDE:");
		ImGui::ShowUserGuide();
	}
	ImGui::End();
}