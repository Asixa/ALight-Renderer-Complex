#pragma once
#include "Panel.h"
#include "Renderer.h"

struct ImVec2;

namespace ALightCreator {
	class Viewport final :public Panel
	{
	public:
		bool overlay = false;
		Renderer* renderer;
		explicit Viewport(Renderer* r) :renderer(r) { r->Init(); }
		void Render() override;
		void Terminate() override;
		void Statistics(ImVec2 window_pos, int w, int h) const;
		void ToolBar() const;
	};
}
