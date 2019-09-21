#include "Inspector.h"
#include "Engine.h"
#include "imgui/imgui.h"
#include "Gizmo/ImGuizmo.h"
#include "Editor.h"

void Inspector::Render()
{
	ImGui::Begin("Inspector", &enabled);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)

	ImGui::ColorEdit3("", reinterpret_cast<float*>(&(Engine::GetInstance().scene->bgColor))); // Edit 3 floats representing a color
	if (ImGui::CollapsingHeader("Transform"))
	{
		if (ImGui::RadioButton("Translate", Editor::mCurrentGizmoOperation == ImGuizmo::TRANSLATE))
			Editor::mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
		ImGui::SameLine();
		if (ImGui::RadioButton("Rotate", Editor::mCurrentGizmoOperation == ImGuizmo::ROTATE))
			Editor::mCurrentGizmoOperation = ImGuizmo::ROTATE;
		ImGui::SameLine();
		if (ImGui::RadioButton("Scale", Editor::mCurrentGizmoOperation == ImGuizmo::SCALE))
			Editor::mCurrentGizmoOperation = ImGuizmo::SCALE;


		ImGui::InputFloat3("Tr", Editor::GetInstance().matrixTranslation, 3);
		ImGui::InputFloat3("Rt", Editor::GetInstance().matrixRotation, 3);
		ImGui::InputFloat3("Sc", Editor::GetInstance().matrixScale, 3);

		if (Editor::mCurrentGizmoOperation != ImGuizmo::SCALE)
{
	if (ImGui::RadioButton("Local", Editor::mCurrentGizmoMode == ImGuizmo::LOCAL))
		Editor::mCurrentGizmoMode = ImGuizmo::LOCAL;
	ImGui::SameLine();
	if (ImGui::RadioButton("World", Editor::mCurrentGizmoMode == ImGuizmo::WORLD))
		Editor::mCurrentGizmoMode = ImGuizmo::WORLD;
}
if (ImGui::IsKeyPressed(83))
Editor::GetInstance().useSnap = !Editor::GetInstance().useSnap;
ImGui::Checkbox("", &Editor::GetInstance().useSnap);
ImGui::SameLine();

switch (Editor::mCurrentGizmoOperation)
{
case ImGuizmo::TRANSLATE:
	ImGui::InputFloat3("Snap", &Editor::GetInstance().snap[0]);
	break;
case ImGuizmo::ROTATE:
	ImGui::InputFloat("Angle Snap", &Editor::GetInstance().snap[0]);
	break;
case ImGuizmo::SCALE:
	ImGui::InputFloat("Scale Snap", &Editor::GetInstance().snap[0]);
	break;
}
ImGui::Checkbox("Bound Sizing", &Editor::GetInstance().boundSizing);
if (Editor::GetInstance().boundSizing)
{
	ImGui::PushID(3);
	ImGui::Checkbox("", &Editor::GetInstance().boundSizingSnap);
	ImGui::SameLine();
	ImGui::InputFloat3("Snap", Editor::GetInstance().boundsSnap);
	ImGui::PopID();
}

	}
	// if (ImGui::CollapsingHeader("Help"))
	// {
	// 	ImGui::Text("PROGRAMMER GUIDE:");
	// 	ImGui::BulletText("Please see the ShowDemoWindow() code in imgui_demo.cpp. <- you are here!");
	// 	ImGui::BulletText("Please see the comments in imgui.cpp.");
	// 	ImGui::BulletText("Please see the examples/ in application.");
	// 	ImGui::BulletText("Enable 'io.ConfigFlags |= NavEnableKeyboard' for keyboard controls.");
	// 	ImGui::BulletText("Enable 'io.ConfigFlags |= NavEnableGamepad' for gamepad controls.");
	// 	ImGui::Separator();
	//
	// 	ImGui::Text("USER GUIDE:");
	// 	ImGui::ShowUserGuide();
	// }
	ImGui::End();
}
