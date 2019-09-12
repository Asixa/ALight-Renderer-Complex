
#include <iostream>
#include "GLRenderer.h"
#include "shader.h"
#include "stb_image.h"
#include "filesystem.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"


void GLRenderer::init_shader()
{
	shaders.emplace_back("shaders/shader.vs", "shaders/shader.fs");
}

void GLRenderer::init_texture()
{
	// unsigned int texture1, texture2;
	// // texture 1
	// // ---------
	// glGenTextures(1, &texture1);
	// glBindTexture(GL_TEXTURE_2D, texture1);
	// // set the texture wrapping parameters
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// // set texture filtering parameters
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// // load image, create texture and generate mipmaps
	// int width, height, nrChannels;
	// stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	// // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	// unsigned char* data = stbi_load(FileSystem::getPath("resources/textures/container.jpg").c_str(), &width, &height, &nrChannels, 0);
	// if (data)
	// {
	// 	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	// 	glGenerateMipmap(GL_TEXTURE_2D);
	// }
	// else
	// {
	// 	std::cout << "Failed to load texture" << std::endl;
	// }
	// stbi_image_free(data);
	// // texture 2
	// // ---------
	// glGenTextures(1, &texture2);
	// glBindTexture(GL_TEXTURE_2D, texture2);
	// // set the texture wrapping parameters
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// // set texture filtering parameters
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// // load image, create texture and generate mipmaps
	// data = stbi_load(FileSystem::getPath("resources/textures/awesomeface.png").c_str(), &width, &height, &nrChannels, 0);
	// if (data)
	// {
	// 	// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
	// 	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	// 	glGenerateMipmap(GL_TEXTURE_2D);
	// }
	// else
	// {
	// 	std::cout << "Failed to load texture" << std::endl;
	// }
	// stbi_image_free(data);
	//
	// // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// // -------------------------------------------------------------------------------------------
	// shaders[0].use(); // don't forget to activate/use the shader before setting uniforms!
	// // either set it manually like so:
	// glUniform1i(glGetUniformLocation(shaders[0].ID, "texture1"), 0);
	// // or set it via the texture class
	// shaders[0].setInt("texture2", 1);
}

void GLRenderer::init_data()
{
	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}


void GLRenderer::render_loop()
{
		shaders[0].use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
}

void GLRenderer::terminate()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
