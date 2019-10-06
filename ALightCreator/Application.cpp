#include "Application.h"
#include <iostream>
#include "Gizmo/ImGuizmo.h"
#include "Input.h"
#include "Style.h"
#include "Resource.h"


void ALightCreator::Application::Run()
{

	InitWindow();
	CreateWindow();
	InitializeOpenGlLoader();
	InitImGui();
	UIlayout->Init();
	Engine::GetInstance().Start();
	MainLoop();
	Terminate();
}

int ALightCreator::Application::InitWindow()
{
	if (!glfwInit()) return 1;
#if __APPLE__
	// GL 3.2 + GLSL 150
	glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
	// GL 3.0 + GLSL 130
	glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_DECORATED, GL_FALSE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif
}

int ALightCreator::Application::CreateWindow()
{
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync
	glfwSetFramebufferSizeCallback(window, OnSizeChangedCallback);
	glfwSetCursorPosCallback(window, MouseCallback);
	glfwSetScrollCallback(window, ScrollCallback);

	// glGenTextures(1, &Resource::icons);
	// glBindTexture(GL_TEXTURE_2D, Resource::icons);
	// int w, h, c;
	// auto data = stbi_load("..\Resources\icons.png", &w, &h, &c, 0);
	// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	// glBindTexture(GL_TEXTURE_2D, 0);
	// GLFWimage images[2];
	// images[0] = load_icon("my_icon.png");
	//glfwSetWindowIcon(window, 0, images);
	Input::GetInstance().window = window;
}

int ALightCreator::Application::InitializeOpenGlLoader()
{
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
	bool err = gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
	bool err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
	bool err = gladLoadGL() == 0;
#else
	bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
#endif
	if (err)
	{
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
		return 1;
	}
}

void ALightCreator::Application::InitImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	//io.ConfigViewportsNoAutoMerge = true;
	//io.ConfigViewportsNoTaskBarIcon = true;
	//
	//ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	
	io.Fonts->AddFontFromFileTTF("../Resources/Fonts/Roboto-Medium.ttf", 14.0f, NULL);
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	Styles::CustomStyle1();
}

void ALightCreator::Application::ImGuiLoop()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	UIlayout->Render();
	ImGui::Render();

}

void ALightCreator::Application::MainLoop()
{
	while (!glfwWindowShouldClose(window))
	{

		glfwPollEvents();
		Engine::GetInstance().Update();
		Input::GetInstance().Clear();
		ProcessInput(window);
		ImGuiLoop();

		glViewport(0, 0, 800, 600);
		glClearColor(0.2f,0.2f,0.2f,1);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		auto& io = ImGui::GetIO(); (void)io;
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			const auto backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault(); glEnable(GL_DEPTH_TEST);
			glfwMakeContextCurrent(backup_current_context);
		}

		glfwSwapBuffers(window);
	}
}

void ALightCreator::Application::Terminate() const
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	UIlayout->Terminate();
	glfwDestroyWindow(window);
	glfwTerminate();
}

void ALightCreator::Application::ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void ALightCreator::Application::OnSizeChangedCallback(GLFWwindow* window, int width, int height)
{
	//glViewport(0, 0, width, height);
}

void ALightCreator::Application::MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	Input::GetInstance().UpdateMouse(xpos, ypos);
}

void ALightCreator::Application::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	Input::GetInstance().MouseScroll = yoffset;

}