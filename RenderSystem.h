#pragma once
#include"GraphicalObject.h"

class RenderSystem
{
public:
	RenderSystem(int WindowSize[2]);
	int GLFWInit();
	int FreeTypeInit();
	int RenderTheQueue();
	void AddToQueue(GraphicalObj* Obj);

private:
	int WindowSize[2] = { 1280, 720 };
	GLFWwindow* window{nullptr};
	vector<GraphicalObj*> RenderQueue{};
	Colors color;
};

