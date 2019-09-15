#include "Viewport.h"
#include "Gizmo/ImGuizmo.h"
#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>


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
void Viewport::Render()
{
	ImGui::Begin("Viewport");

	const auto pos = ImGui::GetWindowPos();
	const auto size = ImGui::GetWindowSize();
	//glViewport(a.x/2, a.y/2, a.x, a.y);

	renderer->resize(size.x, size.y);
	ImGuizmo::BeginFrame(size, pos);
	ImGuizmo::DrawImage(reinterpret_cast<void*>(renderer->frame_buffer()), ImVec2(ImGui::GetCursorScreenPos()),
		ImVec2(ImGui::GetCursorScreenPos().x + size.x - 1, ImGui::GetCursorScreenPos().y + size.y - 1),
		ImVec2(0, 1), ImVec2(1, 0));
	renderer->render_loop();
	
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


