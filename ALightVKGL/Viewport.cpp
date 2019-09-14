#include "Viewport.h"


void Viewport::Render()
{
	ImGui::Begin("Scene Window");

	auto pos = ImGui::GetCursorScreenPos();
	const auto a = ImGui::GetWindowSize();
	auto p = ImGui::GetWindowPos();
	//glViewport(a.x/2, a.y/2, a.x, a.y);

	
	renderer->render_loop();

	ImGui::GetWindowDrawList()->AddImage(
		reinterpret_cast<void*>(renderer->frame_buffer()), ImVec2(ImGui::GetCursorScreenPos()),
		ImVec2(ImGui::GetCursorScreenPos().x + a.x, ImGui::GetCursorScreenPos().y + a.y),
		ImVec2(0, 1), ImVec2(1, 0));

	ImGui::End();
}
