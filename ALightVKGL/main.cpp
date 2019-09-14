
#include "Window.h"
#include "GLRenderer.h"
#include "MainUILayout.h"
#include "Engine.h"

int main()
{
	Window w("ALight GL for CSE410 by Xingyu Chen",1280,720);
	Engine::GetInstance();
	const auto renderer = new GLRenderer();
	w.UIlayout = new MainUILayout(renderer);
	w.renderer = renderer;
	w.run();
	return 0;
}

