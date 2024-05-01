#pragma once
#include"GraphicalObject.h"
#include"Camera.h"

class RenderSystem
{
public:
	RenderSystem(int WindowSize[2]);
	int GLFWInit();
	int FreeTypeInit();
	void process_input(GLFWwindow* window);
	int RenderTheQueue();
	void AddToQueue(GraphicalObj* Obj);
	void CalcDeltaTime();
	float getDeltaTime();

private:
	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame
	float currentFrame = 0.0f;

	int WindowSize[2] = { 1280, 720 };
	GLFWwindow* window{nullptr};
	vector<GraphicalObj*> RenderQueue{};
	Colors color;

	Camera defaultCam;
};

