#pragma once
#include "UILayout.h"
#include "Renderer.h"
#include <vector>
#include "Panel.h"

class MainUILayout:public UILayout
{
public:
	std::vector<Panel*>panels;
	MainUILayout(Renderer* r):renderer(r){}
	unsigned int texture;
	Renderer* renderer;
	bool show_demo_window = true;
	bool show_another_window = true;
	bool show_docking=true;
	void Init() override;
	void Render() override;
	void MenuBar() const;
	void MenuItem() const;
	void DockingSpace(bool* p_open) const;
	
};
