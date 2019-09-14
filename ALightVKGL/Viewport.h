#pragma once
#include "Panel.h"
#include "GLRenderer.h"
class Viewport final :public Panel
{
public:
	Viewport(Renderer* r):renderer(r){}
	Renderer* renderer;
	void Render() override;
};
