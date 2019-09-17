#pragma once
#include "Panel.h"
#include "GLRenderer.h"
class Output:public Panel
{
	ImGuiTextBuffer     Buf;
	ImGuiTextFilter     Filter;
	ImVector<int>       LineOffsets;
public:
	bool AutoScroll;
	void Render() override;
	Output();
	void Clear();
	static Output& GetInstance();
	void AddLog(const char* fmt, ...); 
};

