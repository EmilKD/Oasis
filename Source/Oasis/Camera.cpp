#include "Camera.h"

glm::mat4 Camera::getView() 
{
	return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::setTransform(glm::vec3 pos, glm::vec3 front, glm::vec3 up) 
{
	cameraPos = pos;
	cameraFront = front;
	cameraUp = up;
}