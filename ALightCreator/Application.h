#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <stdio.h>

// Initialize ImGUI
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif
#include <GLFW/glfw3.h>
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

#include "Renderer.h"
#include "UILayout.h"
#include "Engine.h"
namespace ALightCreator {
	
	class Application
	{
	public:
		GLFWwindow* window;
		UILayout* UIlayout;
		Application(const char* title, int w, int h) :title(title), height(h), width(w) {}
		void Run();
	private:
		int width, height;
		const char* glsl_version;
		const char* title;

		int InitWindow();
		int CreateWindow();
		int InitializeOpenGlLoader();
		void InitImGui();
		void ImGuiLoop();
		void MainLoop();
		void Terminate() const;
		
		auto ProcessInput(GLFWwindow* window) -> void;
		static void OnSizeChangedCallback(GLFWwindow* window, int width, int height);
		static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
		static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
	};
}