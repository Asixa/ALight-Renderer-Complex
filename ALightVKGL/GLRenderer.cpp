
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
#include "Gizmo/ImGuizmo.h"


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
void EditTransform(const float* cameraView, float* cameraProjection, float* matrix,ImVec2 size,unsigned f)
{
	static ImGuizmo::OPERATION mCurrentGizmoOperation(ImGuizmo::TRANSLATE);
	static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::LOCAL);
	static bool useSnap = false;
	static float snap[3] = { 1.f, 1.f, 1.f };
	static float bounds[] = { -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f };
	static float boundsSnap[] = { 0.1f, 0.1f, 0.1f };
	static bool boundSizing = false;
	static bool boundSizingSnap = false;

	if (ImGui::IsKeyPressed(90))
		mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
	if (ImGui::IsKeyPressed(69))
		mCurrentGizmoOperation = ImGuizmo::ROTATE;
	if (ImGui::IsKeyPressed(82)) // r Key
		mCurrentGizmoOperation = ImGuizmo::SCALE;
	// if (ImGui::RadioButton("Translate", mCurrentGizmoOperation == ImGuizmo::TRANSLATE))
	// 	mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
	// ImGui::SameLine();
	// if (ImGui::RadioButton("Rotate", mCurrentGizmoOperation == ImGuizmo::ROTATE))
	// 	mCurrentGizmoOperation = ImGuizmo::ROTATE;
	// ImGui::SameLine();
	// if (ImGui::RadioButton("Scale", mCurrentGizmoOperation == ImGuizmo::SCALE))
	// 	mCurrentGizmoOperation = ImGuizmo::SCALE;
	float matrixTranslation[3], matrixRotation[3], matrixScale[3];
	ImGuizmo::DecomposeMatrixToComponents(matrix, matrixTranslation, matrixRotation, matrixScale);

	
	int corner = 0;
	ImGuiIO& io = ImGui::GetIO();
	ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
	ImGui::SetNextWindowBgAlpha(0.0f);
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar;
	ImGui::BeginChild("Child2", size, true, window_flags);


	
	
	// ImGui::InputFloat3("Tr", matrixTranslation, 3);
	// ImGui::InputFloat3("Rt", matrixRotation, 3);
	// ImGui::InputFloat3("Sc", matrixScale, 3);
	ImGuizmo::RecomposeMatrixFromComponents(matrixTranslation, matrixRotation, matrixScale, matrix);

	// if (mCurrentGizmoOperation != ImGuizmo::SCALE)
	// {
	// 	if (ImGui::RadioButton("Local", mCurrentGizmoMode == ImGuizmo::LOCAL))
	// 		mCurrentGizmoMode = ImGuizmo::LOCAL;
	// 	ImGui::SameLine();
	// 	if (ImGui::RadioButton("World", mCurrentGizmoMode == ImGuizmo::WORLD))
	// 		mCurrentGizmoMode = ImGuizmo::WORLD;
	// }
	// if (ImGui::IsKeyPressed(83))
	// 	useSnap = !useSnap;
	// ImGui::Checkbox("", &useSnap);
	// ImGui::SameLine();
	//
	// switch (mCurrentGizmoOperation)
	// {
	// case ImGuizmo::TRANSLATE:
	// 	ImGui::InputFloat3("Snap", &snap[0]);
	// 	break;
	// case ImGuizmo::ROTATE:
	// 	ImGui::InputFloat("Angle Snap", &snap[0]);
	// 	break;
	// case ImGuizmo::SCALE:
	// 	ImGui::InputFloat("Scale Snap", &snap[0]);
	// 	break;
	// }
	// ImGui::Checkbox("Bound Sizing", &boundSizing);
	// if (boundSizing)
	// {
	// 	ImGui::PushID(3);
	// 	ImGui::Checkbox("", &boundSizingSnap);
	// 	ImGui::SameLine();
	// 	ImGui::InputFloat3("Snap", boundsSnap);
	// 	ImGui::PopID();
	// }


	auto a = ImGui::GetWindowPos();
	
	ImGuizmo::SetRect(a.x, a.y, size.x, size.y);

	ImGuizmo::Manipulate(cameraView, cameraProjection, mCurrentGizmoOperation, mCurrentGizmoMode, matrix, NULL, useSnap ? &snap[0] : NULL, boundSizing ? bounds : NULL, boundSizingSnap ? boundsSnap : NULL);
	ImGui::EndChild();
}
float objectMatrix[16] =
{ 1.f, 0.f, 0.f, 0.f,
  0.f, 1.f, 0.f, 0.f,
  0.f, 0.f, 1.f, 0.f,
  0.f, 0.f, 0.f, 1.f };
void GLRenderer::render_loop()
{

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glEnable(GL_DEPTH_TEST);
	backgroundColor = Engine::GetInstance().scene->bgColor;
	glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//ImGuizmo::DrawCube(glm::value_ptr(Camera::main->view), glm::value_ptr(Camera::main->projection), objectMatrix);
	//DrawScene
	shaders[0].use();
	glBindVertexArray(VAO);


	// pass transformation matrices to the shader


	shaders[0].setMat4("projection", Camera::main->projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	shaders[0].setMat4("view", Camera::main->view);




	EditTransform(glm::value_ptr(Camera::main->view), glm::value_ptr(Camera::main->projection), objectMatrix,ImVec2(width,height),frame_buffer());
	// render boxes
	glBindVertexArray(VAO);
	
	{
		// calculate the model matrix for each object and pass it to shader before drawing
		glm::mat4 model = glm::make_mat4(objectMatrix);
		//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		//model = glm::translate(model, Engine::GetInstance().scene->cubePositions[0]);
		//float angle = 20.0f;
		//model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
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
