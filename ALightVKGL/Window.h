#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <stdio.h>

// About OpenGL function loaders: modern OpenGL doesn't have a standard header file and requires individual function pointers to be loaded manually.
// Helper libraries are often used for this purpose! Here we are supporting a few common ones: gl3w, glew, glad.
// You may use another loader/header of your choice (glext, glLoadGen, etc.), or chose to manually implement your own.
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

#include "Renderer.h"
#include "UILayout.h"
class Window
{
public:
	GLFWwindow* window;
	Renderer* renderer;
	UILayout* UIlayout;

	
	Window(const char* title,int w,int h):title(title),height(h),width(w){}
	void custom_style();
	void run()
	{
		init_window();
		create_window();
		initialize_open_gl_loader();
		init_im_gui();
		UIlayout->Init();
		renderer->init_shader();
		renderer->init_data();
		renderer->init_texture();

		main_loop();
		terminate();
	}
private:
	int width, height;
	const char* glsl_version;
	const char* title;

	
	
	int init_window();
	int create_window();
	int initialize_open_gl_loader();
	void init_im_gui();
	void imgui_loop();
	void main_loop();
	void terminate();
	void process_input(GLFWwindow* window);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};
