#pragma once
#include "UILayout.h"
#include "Renderer.h"
#include <vector>
#include "Panel.h"

class MainUILayout:public UILayout
{
public:
	std::vector<Panel*>panels;
	MainUILayout();
	bool show_demo_window = true;
	void Init() override;
	void Render() override;
	void Terminate() override;
	void MenuBar() const;
	void MenuItem() const;
	void DockingSpace(bool* p_open) const;

};
