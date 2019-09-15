#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include <vector>
#include "imgui/imgui.h"
#include "Renderer.h"
class GLRenderer:public Renderer {
public:
	GLRenderer(){}
	ImVec4 backgroundColor = ImVec4(0.2f, 0.2f, 0.2f, 1.00f);
	void init_shader() override;
	void init_texture() override;
	void init_data() override;
	void render_loop() override;
	void terminate() override;
	unsigned int frame_buffer() override;
	void resize(int w,int h)override;
private:
	std::vector<Shader>shaders;
	unsigned int VBO, VAO,EBO;
	unsigned int texture1, texture2;
	unsigned int framebuffer;
	unsigned int textureColorbuffer;
	unsigned int rbo;

	int width = 800, height = 600;
	void InitFrameBuffer(int w, int h);
};

