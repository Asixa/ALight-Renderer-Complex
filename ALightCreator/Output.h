#pragma once
#include "Panel.h"
#include "GLRenderer.h"

namespace ALightCreator {
	class Console :public Panel
	{
		ImGuiTextBuffer     Buf;
		ImGuiTextFilter     Filter;
		ImVector<int>       LineOffsets;
	public:
		bool AutoScroll;
		void Render() override;
		Console();
		void Clear();
		static Console& GetInstance();
		void AddLog(const char* fmt, ...);
	};
}
