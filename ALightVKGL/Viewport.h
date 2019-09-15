#pragma once
#include "Panel.h"
#include "GLRenderer.h"
class Viewport final :public Panel
{
public:
	bool overlay=false;
	Viewport(Renderer* r):renderer(r){}
	Renderer* renderer;
	void Render() override;
};
