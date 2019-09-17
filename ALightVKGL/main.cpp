#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

//This project is dedicated to CSE410 and started on September 10th 2019
#include "Window.h"
#include "GLRenderer.h"
#include "MainUILayout.h"
#include "Engine.h"

int main()
{
	Window w("ALight Creator [CSE410 by Xingyu Chen]",1280,720);
	Engine::GetInstance();
	const auto renderer = new GLRenderer();
	w.UIlayout = new MainUILayout(renderer);
	w.renderer = renderer;
	w.run();
	return 0;
}

