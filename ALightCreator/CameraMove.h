#pragma once
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Component.h"
#include "Transform.h"
#include <glm/glm.hpp>

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Input.h"
using namespace ALightCreator;
// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class CameraMove:public Component
{
public:
	// Camera Attributes
	//glm::vec3 Position;

	
	// Euler Angles
	// float Yaw;
	// float Pitch;
	// Camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	// Constructor with vectors
	void Init(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) 
	{
		transform->position = position;
		MovementSpeed = SPEED;
		MouseSensitivity = SENSITIVITY;
		Zoom=ZOOM;
		transform->Front = glm::vec3(0.0f, 0.0f, -1.0f);
		transform->rotation.y= yaw;
		transform->rotation.x=pitch;
		
	}
	// Constructor with scalar values
	void Init(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) 
	{
		transform->position = glm::vec3(posX, posY, posZ);
		MovementSpeed = SPEED;
		MouseSensitivity = SENSITIVITY;
		Zoom = ZOOM;
		transform->Front = glm::vec3(0.0f, 0.0f, -1.0f);
		transform->rotation.y = yaw;
		transform->rotation.x = pitch;
		
	}

	void Update() override
	{
		// if (ImGui::IsKeyPressed(GLFW_KEY_W))
		// 	ProcessKeyboard(FORWARD, ImGui::GetIO().DeltaTime);
		// if (ImGui::IsKeyPressed(GLFW_KEY_S))
		// 	ProcessKeyboard(BACKWARD, ImGui::GetIO().DeltaTime);
		// if (ImGui::IsKeyPressed(GLFW_KEY_A))
		// 	ProcessKeyboard(LEFT, ImGui::GetIO().DeltaTime);
		// if (ImGui::IsKeyPressed(GLFW_KEY_D))
		// 	ProcessKeyboard(RIGHT, ImGui::GetIO().DeltaTime);



		
		if (ImGui::IsMouseDown(GLFW_MOUSE_BUTTON_RIGHT)) {
			glfwSetInputMode(Input::GetInstance().window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			ProcessMouseMovement(Input::GetInstance().MouseXoffset, Input::GetInstance().MouseYoffset);

			if (Input::GetInstance().KeyPress(GLFW_KEY_W))
				ProcessKeyboard(FORWARD, ImGui::GetIO().DeltaTime);
			if (Input::GetInstance().KeyPress(GLFW_KEY_S))
				ProcessKeyboard(BACKWARD, ImGui::GetIO().DeltaTime);
			if (Input::GetInstance().KeyPress(GLFW_KEY_A))
				ProcessKeyboard(LEFT, ImGui::GetIO().DeltaTime);
			if (Input::GetInstance().KeyPress(GLFW_KEY_D))
				ProcessKeyboard(RIGHT, ImGui::GetIO().DeltaTime);
		}
		else
		{
			glfwSetInputMode(Input::GetInstance().window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		//ProcessMouseScroll(Input::GetInstance().MouseScroll);
		
	}
	// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(transform->position, transform->position + transform->Front, transform->Up);
	}

	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		float velocity = MovementSpeed * deltaTime;
		if (direction == FORWARD)
			transform->position += transform->Front * velocity;
		if (direction == BACKWARD)
			transform->position -= transform->Front * velocity;
		if (direction == LEFT)
			transform->position -= transform->Right * velocity;
		if (direction == RIGHT)
			transform->position += transform->Right * velocity;
	}

	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
	{
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		transform->rotation.y += xoffset;
		transform->rotation.x += yoffset;

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch)
		{
			if (transform->rotation.x > 89.0f)
				transform->rotation.x = 89.0f;
			if (transform->rotation.x < -89.0f)
				transform->rotation.x = -89.0f;
		}
	}

	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(float yoffset)
	{
		if (Zoom >= 1.0f && Zoom <= 45.0f)
			Zoom -= yoffset;
		if (Zoom <= 1.0f)
			Zoom = 1.0f;
		if (Zoom >= 45.0f)
			Zoom = 45.0f;
		Camera::main->FOV = Zoom;
	}

};