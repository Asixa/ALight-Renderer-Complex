
#include <iostream>
#include "GLRenderer.h"
#include "shader.h"


#include "filesystem.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Engine.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"


void GLRenderer::init_shader()
{

	shaders.emplace_back("shaders/shader.vs", "shaders/shader.fs");
	//shaders.push_back(new Shader("shaders/shader.vs", "shaders/shader.fs"));
}

void GLRenderer::init_texture()
{
	auto t1=Texture("../Resources/box3.png");

	auto t2 = Texture("../Resources/UB.png");
	shaders[0].use();
	shaders[0].setInt("texture1", 1);
	shaders[0].setInt("texture2", 2);


}

void GLRenderer::init_data()
{
	

	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Engine::GetInstance().scene->vertices), Engine::GetInstance().scene->vertices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Engine::GetInstance().scene->indices), Engine::GetInstance().scene->indices, GL_STATIC_DRAW);
	//
	// // position attribute
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), static_cast<void*>(0));
	// glEnableVertexAttribArray(0);
	// // color attribute
	// glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	// glEnableVertexAttribArray(1);
	// // texture coord attribute
	// glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
	// glEnableVertexAttribArray(2);

	InitFrameBuffer(800, 600);
}


void GLRenderer::render_loop()
{

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glEnable(GL_DEPTH_TEST);
	backgroundColor = Engine::GetInstance().scene->bgColor;
	glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	//DrawScene
	shaders[0].use();
	glBindVertexArray(VAO);


	// pass transformation matrices to the shader


	shaders[0].setMat4("projection", Camera::main->projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	shaders[0].setMat4("view", Camera::main->view);

	// render boxes
	glBindVertexArray(VAO);
	
	{
		// calculate the model matrix for each object and pass it to shader before drawing
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		model = glm::translate(model, Engine::GetInstance().scene->cubePositions[0]);
		float angle = 20.0f;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		shaders[0].setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void GLRenderer::terminate()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

unsigned GLRenderer::frame_buffer()
{
	return textureColorbuffer;
}

void GLRenderer::resize(int w, int h)
{
	width = w;
	height = h;
	Camera::main->width = w;
	Camera::main->height = h;
	
}

void GLRenderer::InitFrameBuffer(int w,int h)
{
	// framebuffer configuration
	// -------------------------
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	// create a color attachment texture
	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	return;
	glGenFramebuffers(1, &framebuffer);
	glActiveTexture(GL_TEXTURE0);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	// create a color attachment texture
	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
	glBindTexture(1, 0);
	// // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	// glGenRenderbuffers(1, &rbo);
	// glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	// glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600); // use a single renderbuffer object for both a depth AND stencil buffer.
	// glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
	// // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	// if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	// 	std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	// glBindFramebuffer(GL_FRAMEBUFFER, 0);

}
