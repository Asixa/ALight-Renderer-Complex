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
	void resize(int w,int h);
private:
	std::vector<Shader*>shaders;
	unsigned int VBO, VAO,EBO;
	unsigned int texture1, texture2;
	unsigned int framebuffer;
	unsigned int textureColorbuffer;
	unsigned int rbo;

	float vertices[32] = {
		//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
	};
	unsigned int indices[6] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};
	void InitFrameBuffer(int w, int h);
};

