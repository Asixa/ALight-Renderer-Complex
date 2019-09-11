#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include <vector>
#include "imgui/imgui.h"

class GLRenderer {
public:
	GLRenderer(){}
	void run();
private:
	std::vector<Shader>shaders;
	unsigned int VBO, VAO;
	void init_shader();
	void init_texture();
	void setup_data();
	void render_loop();
	void terminate();
};

