
// #include "GLRenderer.h"

#include "Window.h"
#include "GLRenderer.h"

int main()
{
	Window w("CSE410 intro to CG",1280,720);
	w.renderer = new GLRenderer();
	w.run();
	return 0;
}
