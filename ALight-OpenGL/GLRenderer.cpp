
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
	//Resource::GetInstance().shaders.push_back(new Shader("shaders/1.model_loading.vs", "shaders/1.model_loading.fs"));
	Resource::GetInstance().shaders.push_back(new Shader("shaders/shader.vs", "shaders/shader.fs"));
	for (auto& shader : Resource::GetInstance().shaders)
		GLResource::GetInstance().GLShaders.push_back(new GLShader(shader));
}

void GLRenderer::InitTexture()
{
	for (auto& texture : Resource::GetInstance().textures)GLResource::GetInstance().textures.push_back(new GLTexture(texture));
}

void GLRenderer::InitData()
{
	our_model = new GLModel(Engine::GetInstance().scene->m);
	//our_model = new GLModel(new Model(Engine::GetInstance().scene->path));

	InitFrameBuffer(800, 600);
}

void GLRenderer::Reload()
{
	our_model = new GLModel(Engine::GetInstance().scene->m);
}


void GLRenderer::Update()
{
	if(Engine::GetInstance().scene->changed)
	{
		Reload();
		Engine::GetInstance().scene->changed = false;
		
	}

	glBindFramebuffer(GL_FRAMEBUFFER, framebufferPointer);
	glEnable(GL_DEPTH_TEST);
	auto backgroundColor = Engine::GetInstance().scene->bgColor;
	glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// DrawScene
	GLResource::GetInstance().GLShaders[0]->use();


	GLResource::GetInstance().GLShaders[0]->setVec3("objectColor", 0.5f, 0.5f, 0.5f);
	GLResource::GetInstance().GLShaders[0]->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos(1.2f, -1.0f, 2.5f);
	GLResource::GetInstance().GLShaders[0]->setVec3("lightPos",lightPos );

	
	GLResource::GetInstance().GLShaders[0]->setMat4("projection", Camera::main->projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	GLResource::GetInstance().GLShaders[0]->setMat4("view", Camera::main->view);


	glm::mat4 model = glm::make_mat4(Engine::GetInstance().scene->objectMatrix);



	 auto scene = Engine::GetInstance().scene;
	 model = model = glm::translate(model, scene->InitTranslation);
	 model = model = glm::scale(model, scene->InitScale);
	 model = model = glm::rotate(model, scene->InitRotateDegree, scene->InitRotateAxis);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	GLResource::GetInstance().GLShaders[0]->setMat4("model", model);
	our_model->Draw(*GLResource::GetInstance().GLShaders[0]);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void GLRenderer::Terminate()
{

}
void Split()
{
	auto mesh = our_model->meshes[0];
	
}

unsigned GLRenderer::FrameBuffer()
{
	return frameColorBuffer;
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
	glGenFramebuffers(1, &framebufferPointer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebufferPointer);
	// create a color attachment texture
	glGenTextures(1, &frameColorBuffer);
	glBindTexture(GL_TEXTURE_2D, frameColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameColorBuffer, 0);
	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)

	glGenRenderbuffers(1, &frameDepthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, frameDepthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, frameDepthBuffer); // now actually attach it
	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}
