#pragma once
#include<glm/glm.hpp>

class Camera
{
public:
	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

private:

};

