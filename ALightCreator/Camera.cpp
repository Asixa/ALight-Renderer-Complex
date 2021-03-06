#include "Camera.h"

#include "Transform.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace ALightCreator;
Camera* Camera::main = nullptr;
void Camera::Update()
{
	view = glm::lookAt(transform->position, transform->position + transform->Front, transform->Up);
	projection= glm::perspective(glm::radians(FOV), static_cast<float>(width) / static_cast<float>(height), near, far);
}

Camera::Camera()
{
	main = this;
}
