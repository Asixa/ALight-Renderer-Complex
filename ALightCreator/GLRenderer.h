#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include <vector>
#include "imgui/imgui.h"
#include "Renderer.h"
#include "MyTexture.h"
class GLRenderer:public Renderer {
public:
	GLRenderer(){}
	ImVec4 backgroundColor = ImVec4(0.2f, 0.2f, 0.2f, 1.00f);
	void Init() override;
	void InitShader();
	void InitTexture();
	void InitData();
	void RenderLoop() override;
	void Terminate() override;
	unsigned int FrameBuffer() override;
	void Resize(int w,int h)override;
private:
	std::vector<Shader>shaders;
	
	unsigned int VBO, VAO,EBO;
	unsigned int texture1, texture2;
	unsigned int framebuffer;
	unsigned int textureColorbuffer;
	unsigned int rbo;
	// ourModel = new Model("../Resources/Objects/nanosuit/nanosuit.obj");
	int width = 800, height = 600;
	void InitFrameBuffer(int w, int h);
};

