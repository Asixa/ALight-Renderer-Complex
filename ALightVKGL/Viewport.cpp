#include "Viewport.h"
#include "Gizmo/ImGuizmo.h"
#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include "Engine.h"


void Overlay(ImVec2 window_pos,int w,int h)
{
	int corner = -1;
	ImGuiIO& io = ImGui::GetIO();
	ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
	ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
	ImGui::SetNextWindowBgAlpha(0.35f);
	ImGuiWindowFlags window_flags =   ImGuiWindowFlags_NoScrollWithMouse| ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar;
	ImGui::BeginChild("Child1", ImVec2(w, h), true, window_flags);

	
	ImGui::Text("Statistics\n");
	ImGui::Separator();
	ImGui::Text("%.1f FPS (%.3f ms/frame)", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);
	if (ImGui::IsMousePosValid())
		ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
	else
		ImGui::Text("Mouse Position: <invalid>");
	ImGui::EndChild();

}
void FullOverLay(ImVec2 pos, ImVec2 size)
{
	int corner = 0;
	ImGuiIO& io = ImGui::GetIO();
	ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
	ImGui::SetNextWindowPos(pos, ImGuiCond_Always, window_pos_pivot);
	ImGui::SetNextWindowBgAlpha(0.5f);
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar;
	ImGui::BeginChild("Child2", size, true, window_flags);
	
	
	ImGuizmo::SetRect(pos.x, pos.y, size.x, size.y);
	ImGui::Text("Statistics\n");
	ImGui::Separator();

	ImGui::EndChild();
}
void ToolBar2()
{
	static int item_current_2;
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0);
	ImGui::SetCursorPosY(25);
	ImGui::SetNextItemWidth(80);
	
	ImGui::Combo("2", &item_current_2, "aaaa\0bbbb\0cccc\0dddd\0eeee\0\0");

	ImGui::SetCursorPos(ImVec2(88, 25));
	ImGui::Button("Clear");


	


	ImGui::PopStyleVar();
}
void EditTransform(const float* cameraView, float* cameraProjection, float* matrix, ImVec2 size)
{
	static ImGuizmo::OPERATION mCurrentGizmoOperation(ImGuizmo::TRANSLATE);
	static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::LOCAL);
	static bool useSnap = false;
	static float snap[3] = { 1.f, 1.f, 1.f };
	static float bounds[] = { -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f };
	static float boundsSnap[] = { 0.1f, 0.1f, 0.1f };
	static bool boundSizing = false;
	static bool boundSizingSnap = false;

	if (ImGui::IsKeyPressed(90))
		mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
	if (ImGui::IsKeyPressed(69))
		mCurrentGizmoOperation = ImGuizmo::ROTATE;
	if (ImGui::IsKeyPressed(82)) // r Key
		mCurrentGizmoOperation = ImGuizmo::SCALE;

	// if (ImGui::RadioButton("Translate", mCurrentGizmoOperation == ImGuizmo::TRANSLATE))
	// 	mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
	// ImGui::SameLine();
	// if (ImGui::RadioButton("Rotate", mCurrentGizmoOperation == ImGuizmo::ROTATE))
	// 	mCurrentGizmoOperation = ImGuizmo::ROTATE;
	// ImGui::SameLine();
	// if (ImGui::RadioButton("Scale", mCurrentGizmoOperation == ImGuizmo::SCALE))
	// 	mCurrentGizmoOperation = ImGuizmo::SCALE;
	float matrixTranslation[3], matrixRotation[3], matrixScale[3];
	ImGuizmo::DecomposeMatrixToComponents(matrix, matrixTranslation, matrixRotation, matrixScale);


	ImGuiIO& io = ImGui::GetIO();


	//ImGuizmo::DrawGrid(cameraView, cameraProjection, glm::value_ptr(glm::mat4(1.0f)), 10.f);


	//ImGui::InputFloat3("Tr", matrixTranslation, 3);
	// ImGui::InputFloat3("Rt", matrixRotation, 3);
	// ImGui::InputFloat3("Sc", matrixScale, 3);
	ImGuizmo::RecomposeMatrixFromComponents(matrixTranslation, matrixRotation, matrixScale, matrix);

	// if (mCurrentGizmoOperation != ImGuizmo::SCALE)
	// {
	// 	if (ImGui::RadioButton("Local", mCurrentGizmoMode == ImGuizmo::LOCAL))
	// 		mCurrentGizmoMode = ImGuizmo::LOCAL;
	// 	ImGui::SameLine();
	// 	if (ImGui::RadioButton("World", mCurrentGizmoMode == ImGuizmo::WORLD))
	// 		mCurrentGizmoMode = ImGuizmo::WORLD;
	// }
	// if (ImGui::IsKeyPressed(83))
	// 	useSnap = !useSnap;
	// ImGui::Checkbox("", &useSnap);
	// ImGui::SameLine();
	//
	// switch (mCurrentGizmoOperation)
	// {
	// case ImGuizmo::TRANSLATE:
	// 	ImGui::InputFloat3("Snap", &snap[0]);
	// 	break;
	// case ImGuizmo::ROTATE:
	// 	ImGui::InputFloat("Angle Snap", &snap[0]);
	// 	break;
	// case ImGuizmo::SCALE:
	// 	ImGui::InputFloat("Scale Snap", &snap[0]);
	// 	break;
	// }
	// ImGui::Checkbox("Bound Sizing", &boundSizing);
	// if (boundSizing)
	// {
	// 	ImGui::PushID(3);
	// 	ImGui::Checkbox("", &boundSizingSnap);
	// 	ImGui::SameLine();
	// 	ImGui::InputFloat3("Snap", boundsSnap);
	// 	ImGui::PopID();
	// }


	auto a = ImGui::GetWindowPos();

	ImGuizmo::SetRect(a.x, a.y, size.x, size.y);

	ImGuizmo::Manipulate(cameraView, cameraProjection, mCurrentGizmoOperation, mCurrentGizmoMode, matrix, NULL, useSnap ? &snap[0] : NULL, boundSizing ? bounds : NULL, boundSizingSnap ? boundsSnap : NULL);

}
void Viewport::Render()
{
	ImGui::Begin("Scene");
	
	const auto pos = ImGui::GetWindowPos();
	const auto size = ImGui::GetWindowSize();
	//glViewport(a.x/2, a.y/2, a.x, a.y);
	//ImGui::SetCursorPosY(0);
	renderer->resize(size.x, size.y);
	
	ImGuizmo::BeginFrame(size, pos);
	
	ImGuizmo::DrawImage(reinterpret_cast<void*>(renderer->frame_buffer()), ImVec2(ImGui::GetCursorScreenPos()),
		ImVec2(ImGui::GetCursorScreenPos().x + size.x - 1, ImGui::GetCursorScreenPos().y + size.y - 1),
		ImVec2(0, 1), ImVec2(1, 0));
	EditTransform(glm::value_ptr(Camera::main->view), glm::value_ptr(Camera::main->projection), Engine::GetInstance().scene->objectMatrix, ImVec2(size.x, size.y));
	renderer->render_loop();
	ToolBar2();
	// ImGui::GetWindowDrawList()->AddImage(
	// 	reinterpret_cast<void*>(renderer->frame_buffer()), ImVec2(ImGui::GetCursorScreenPos()),
	// 	ImVec2(ImGui::GetCursorScreenPos().x + size.x-1, ImGui::GetCursorScreenPos().y + size.y-1),
	// 	ImVec2(0, 1), ImVec2(1, 0));
	
	

	
	Overlay(ImVec2(pos.x + size.x - 10, pos.y +60+30),220,60);
	//FullOverLay(ImVec2(pos.x , pos.y), size);
	//ImGui::BeginChild("Gizmo", size, false, ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar);
	//ImGuizmo::SetRect(pos.x, pos.y, size.x, size.y);
	//ImGui::EndChild();
	
	ImGui::End();
}


