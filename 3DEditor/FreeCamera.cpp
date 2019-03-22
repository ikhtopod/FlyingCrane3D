#include "FreeCamera.h"


void FreeCamera::keyboardInput() {
	Application* appThis = Application::getInstancePtr();
	GLFWwindow* window = appThis->getWindow().getWindowPtr();
	DeltaTime& delta = appThis->getDeltaTime();

	float velocity = this->speedMovement * delta;

	glm::vec3 pos = this->transform.getPosition();

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		pos += this->axis.getFront() * velocity;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		pos += this->axis.getRight() * velocity;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		pos += this->axis.getUp() * velocity;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		pos -= this->axis.getFront() * velocity;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		pos -= this->axis.getRight() * velocity;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		pos -= this->axis.getUp() * velocity;

	this->transform.setPosition(pos);
}


void FreeCamera::mouseInput(float xPos, float yPos) {
	glm::vec3 _rotation = this->transform.getRotation();

	_rotation.x += (lastMousePosition.y - yPos) * this->mouseSensitivity.x;
	_rotation.y += (xPos - lastMousePosition.x) * this->mouseSensitivity.y;

	lastMousePosition = glm::vec2 { xPos, yPos };

	_rotation.x = std::clamp<float>(_rotation.x, MIN_MOUSE_PITCH, MAX_MOUSE_PITCH);
	_rotation.y = Util::repeat(_rotation.y, MIN_MOUSE_YAW, MAX_MOUSE_YAW);

	this->transform.setRotation(_rotation);

	this->updateCameraVectors();
}
