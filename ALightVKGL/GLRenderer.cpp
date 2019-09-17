
#include <iostream>
#include "GLRenderer.h"
#include "shader.h"


#include "filesystem.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Engine.h"
#include "MyTexture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Gizmo/ImGuizmo.h"
#include "Output.h"


void GLRenderer::init_shader()
{

	shaders.emplace_back("shaders/1.model_loading.vs", "shaders/1.model_loading.fs");
	//shaders.emplace_back("shaders/shader.vs", "shaders/shader.fs");
}

void GLRenderer::init_texture()
{
	// auto t1=MyTexture("../Resources/box3.png");
	// auto t2 = MyTexture("../Resources/UB.png");
	// shaders[0].use();
	// shaders[0].setInt("texture1", 1);
	// shaders[0].setInt("texture2", 2);


}
Model* ourModel; 
void GLRenderer::init_data()
{
	
	ourModel = new Model("../Resources/Objects/sponzaLarge/sponza2.obj");

	std::cout << "Hello 网格数量:" << ourModel->meshes.size()<< std::endl;
	Output::GetInstance().AddLog("233");
	//
	// glGenVertexArrays(1, &VAO);
	// glGenBuffers(1, &VBO);
	// glGenBuffers(1, &EBO);
	//
	// glBindVertexArray(VAO);
	//
	// glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(Engine::GetInstance().scene->vertices), Engine::GetInstance().scene->vertices, GL_STATIC_DRAW);
	//
	//
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	// glEnableVertexAttribArray(0);
	// glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	// glEnableVertexAttribArray(1);
	

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
	shaders[0].setMat4("projection", Camera::main->projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	shaders[0].setMat4("view", Camera::main->view);



	// render boxes



	glm::mat4 model = glm::make_mat4(Engine::GetInstance().scene->objectMatrix);
	 model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
	 model = glm::scale(model, glm::vec3(0.002f, 0.002f, 0.002f));	
	shaders[0].setMat4("model", model);
	ourModel->Draw(shaders[0]);
	//glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 36);

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
