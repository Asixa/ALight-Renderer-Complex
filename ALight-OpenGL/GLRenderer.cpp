
#include <iostream>
#include "GLRenderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GLModel.h"
#include "../ALightCreator/Engine.h"
#include "../ALightCreator/Camera.h"
using namespace ALightCreator;
using namespace ALight_OpenGL;
GLModel* our_model;
void GLRenderer::Init()
{
	InitShader();
	InitData();
	InitTexture();
}

void GLRenderer::InitShader()
{
	for (auto shader : shaders)GLShaders.emplace_back(&shader);
	//GLShaders.emplace_back("shaders/1.model_loading.vs", "shaders/1.model_loading.fs");
}

void GLRenderer::InitTexture()
{
}

void GLRenderer::InitData()
{
	
	our_model = new GLModel(new Model("../Resources/Objects/sponzaLarge/sponza.obj"));
	InitFrameBuffer(800, 600);
}


void GLRenderer::RenderLoop()
{

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glEnable(GL_DEPTH_TEST);
	auto backgroundColor = Engine::GetInstance().scene->bgColor;
	glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// DrawScene
	GLShaders[0].use();
	GLShaders[0].setMat4("projection", Camera::main->projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	GLShaders[0].setMat4("view", Camera::main->view);


	glm::mat4 model = glm::make_mat4(Engine::GetInstance().scene->objectMatrix);
	model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
	model = glm::scale(model, glm::vec3(0.002f, 0.002f, 0.002f));
	GLShaders[0].setMat4("model", model);
	our_model->Draw(GLShaders[0]);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void GLRenderer::Terminate()
{

}

unsigned GLRenderer::FrameBuffer()
{
	return textureColorbuffer;
}

void GLRenderer::Resize(int w, int h)
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

}
