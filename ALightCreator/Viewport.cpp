#include "Viewport.h"

#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include "Engine.h"
#include "Editor.h"
using namespace ALightCreator;

void Viewport::Statistics(ImVec2 window_pos,int w,int h) const
{
	auto corner = -1;
	auto& io = ImGui::GetIO();
	const auto window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
	ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
	ImGui::SetNextWindowBgAlpha(0.35f);
	const auto window_flags =   ImGuiWindowFlags_NoScrollWithMouse| ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar;
	ImGui::BeginChild("Child", ImVec2(w, h), true, window_flags);
	ImGui::Text("Statistics\n");
	ImGui::Separator();
	ImGui::Text("%.1f FPS (%.3f ms/frame)", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);
	if (ImGui::IsMousePosValid())
		ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
	else
		ImGui::Text("Mouse Position: <invalid>");
	ImGui::EndChild();

}
void Viewport::ToolBar() const
{
	static int item_current_2;
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0);
	ImGui::SetCursorPosY(25);
	ImGui::SetNextItemWidth(80);
	
	ImGui::Combo(" ", &item_current_2, "aaaa\0bbbb\0cccc\0dddd\0eeee\0\0");

	ImGui::SetCursorPos(ImVec2(88, 25));
	ImGui::Button("Clear");

	ImGui::PopStyleVar();
}




void Viewport::Render() 
{
	ImGui::Begin("Scene");
	const auto pos = ImGui::GetWindowPos();
	const auto size = ImGui::GetWindowSize();
	renderer->Resize(size.x, size.y);
	ImGuizmo::BeginFrame(size, pos);
	ImGuizmo::DrawImage(reinterpret_cast<void*>(renderer->FrameBuffer()), ImVec2(ImGui::GetCursorScreenPos()),
		ImVec2(ImGui::GetCursorScreenPos().x + size.x - 1, ImGui::GetCursorScreenPos().y + size.y - 1),
		ImVec2(0, 1), ImVec2(1, 0));
	if(Editor::GetInstance().visible)Editor::GetInstance().EditTransform(glm::value_ptr(Camera::main->view), glm::value_ptr(Camera::main->projection), Engine::GetInstance().scene->objectMatrix, ImVec2(size.x, size.y));
	renderer->Update();
	ToolBar();
	Statistics(ImVec2(pos.x + size.x - 10, pos.y +60+30),220,60);

	ImGui::End();
}

void Viewport::Terminate()
{
	renderer->Terminate();
	free(renderer);
}


