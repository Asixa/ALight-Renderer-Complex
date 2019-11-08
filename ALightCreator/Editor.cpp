#include "Editor.h"
#include "imgui/imgui.h"
#include "Gizmo/ImGuizmo.h"
using namespace ALightCreator;
ImGuizmo::OPERATION Editor::mCurrentGizmoOperation(ImGuizmo::TRANSLATE);
ImGuizmo::MODE  Editor::mCurrentGizmoMode(ImGuizmo::LOCAL);
void ALightCreator::Editor::EditTransform(const float* cameraView, float* cameraProjection, float* matrix, ImVec2 size)
{
	
	if (ImGui::IsKeyPressed(90))mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
	if (ImGui::IsKeyPressed(69))mCurrentGizmoOperation = ImGuizmo::ROTATE;
	if (ImGui::IsKeyPressed(82)) mCurrentGizmoOperation = ImGuizmo::SCALE;
	ImGuizmo::DecomposeMatrixToComponents(matrix, matrixTranslation, matrixRotation, matrixScale);
	ImGuiIO& io = ImGui::GetIO();
	ImGuizmo::RecomposeMatrixFromComponents(matrixTranslation, matrixRotation, matrixScale, matrix);
	const auto a = ImGui::GetWindowPos();
	ImGuizmo::SetRect(a.x, a.y, size.x, size.y);
	ImGuizmo::Manipulate(cameraView, cameraProjection, mCurrentGizmoOperation, mCurrentGizmoMode, matrix, NULL, useSnap ? &snap[0] : NULL, boundSizing ? bounds : NULL, boundSizingSnap ? boundsSnap : NULL);
}
