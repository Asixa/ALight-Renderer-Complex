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

	void init_shader() override;
	void init_texture() override;
	void init_data() override;
	void render_loop() override;
	void terminate() override;
private:
	std::vector<Shader>shaders;
	unsigned int VBO, VAO;
};

