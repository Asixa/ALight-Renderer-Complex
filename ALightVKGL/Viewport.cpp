#include "Viewport.h"



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

void Viewport::Render()
{
	ImGui::Begin("Viewport");
	

	const auto a = ImGui::GetWindowSize();
	auto p = ImGui::GetWindowPos();
	//glViewport(a.x/2, a.y/2, a.x, a.y);

	renderer->resize(a.x, a.y);
	renderer->render_loop();

	ImGui::GetWindowDrawList()->AddImage(
		reinterpret_cast<void*>(renderer->frame_buffer()), ImVec2(ImGui::GetCursorScreenPos()),
		ImVec2(ImGui::GetCursorScreenPos().x + a.x-1, ImGui::GetCursorScreenPos().y + a.y-1),
		ImVec2(0, 1), ImVec2(1, 0));

	auto pos = ImGui::GetWindowPos();
	auto size = ImGui::GetWindowSize;

	Overlay(ImVec2(pos.x + size().x - 10, pos.y +60+30),220,60);

	ImGui::End();
}


