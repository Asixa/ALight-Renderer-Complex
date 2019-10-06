#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif


//This project is dedicated to CSE410 and started on September 10th 2019
#include "Application.h"
#include "MainUILayout.h"
#include "Editor.h"
GLuint ALightCreator::Editor::icons = 0;
int main()
{
	ALightCreator::Application app("ALight Creator [CSE410 by Xingyu Chen]", 1280, 720);
	app.UIlayout = new ALightCreator::MainUILayout();
	app.Run();

	return 0;
}
