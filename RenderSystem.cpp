#include "RenderSystem.h"

//---------------------------- Variables and Objects declaration


int WindowSize[2] = { 1280,720 };

bool left_mouse_button, right_mouse_button;
float g_xpos, g_ypos, wc_x, wc_y, Scale_x = 0.05f, Scale_y = Scale_x;

struct KeyFlags
{
	bool UpKeyPressed{ false };
	bool LeftKeyPressed{ false };
	bool RightKeyPressed{ false };
	bool DownKeyPressed{ false };
};


KeyFlags flags;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

//--------------------------------------------------- CallBacks 
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	const float cameraSpeed = 0.05f; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void cursor_pos_callBack(GLFWwindow* window, double xpos, double ypos)
{
	g_xpos = xpos;
	g_ypos = ypos;
	wc_x = (2 * (xpos / WindowSize[0]) - 1) / Scale_x;
	wc_y = (-2 * (ypos / WindowSize[1]) + 1) / Scale_y;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	if (!(flags.UpKeyPressed && flags.RightKeyPressed && flags.LeftKeyPressed && flags.DownKeyPressed))
	{
		if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		{
			flags.UpKeyPressed = true;
		}
		else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
		{
			flags.LeftKeyPressed = true;
		}
		else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		{
			flags.RightKeyPressed = true;
		}
		else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		{
			flags.DownKeyPressed = true;
		}
	}
	else
	{
		if (key == GLFW_KEY_UP && action == GLFW_RELEASE)
		{
			flags.UpKeyPressed = false;
		}
		else if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
		{
			flags.LeftKeyPressed = false;
		}
		else if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
		{
			flags.RightKeyPressed = false;
		}
		else if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
		{
			flags.DownKeyPressed = false;
		}
	}
}

void mouse_clicked(GLFWwindow* window, int button, int action, int mod)
{
	left_mouse_button = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1);
	right_mouse_button = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2);
}


RenderSystem::RenderSystem(int window_size[2]) : WindowSize{ window_size[0], window_size[1] }
{
	
	glfwInit();

	// setting window hints aka OpenGL version and profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// setting up the window and error handling
	window = glfwCreateWindow(WindowSize[0], WindowSize[1], "Pathfinder", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "window failed to Initialize";
		//return -1;
	}

	// setting the window as OpendGl's current context
	glfwMakeContextCurrent(window);

	//Turning VSync Off! :/
	glfwSwapInterval(0);

	// glad loading error handling
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		//return -1;
	}

	// CallBacks -----------------------------------------------
	// updating viewport size if window size is changed CallBack
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, cursor_pos_callBack);
	glfwSetMouseButtonCallback(window, mouse_clicked);
	glfwSetKeyCallback(window, key_callback);


}

int RenderSystem::GLFWInit() 
{
	// GLFW initialization ----------------------------------------
	glfwInit();

	// setting window hints aka OpenGL version and profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// setting up the window and error handling
	window = glfwCreateWindow(WindowSize[0], WindowSize[1], "Pathfinder", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "window failed to Initialize";
		return -1;
	}

	// setting the window as OpendGl's current context
	glfwMakeContextCurrent(window);

	//Turning VSync Off! :/
	glfwSwapInterval(0);

	// glad loading error handling
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// CallBacks -----------------------------------------------
	// updating viewport size if window size is changed CallBack
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, cursor_pos_callBack);
	glfwSetMouseButtonCallback(window, mouse_clicked);
	glfwSetKeyCallback(window, key_callback);
}

int RenderSystem::FreeTypeInit() 
{
	// FreeType Init -------------------------------------------
	//FT_Library ftlib;

	//if (FT_Init_FreeType(&ftlib))
	//{
	//	cout << "ERROR::FreeType: FreeType library failed to initialize." << endl;
	//	return -1;
	//}

	//FT_Face ftface;

	//if (FT_New_Face(ftlib, "fonts/arial.ttf", 0, &ftface))
	//{
	//	cout << "ERROR::FreeType: Failed to load font." << endl;
	//	return -1;
	//}
	return -1;
}

int RenderSystem::RenderTheQueue()
{
	
	glEnable(GL_DEPTH_TEST);
	
	while (!glfwWindowShouldClose(window))
	{
		// GLFW background setup

		process_input(window);
		//Camera

		glfwSwapBuffers(window);
		glfwPollEvents();
		glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		if (!RenderQueue.empty())
		{
			for (GraphicalObj* GObj : RenderQueue)
			{
				GObj->DrawShape(color.White);
			}
		}
	}

	// Unbinding and closing all glfw windows and clearing opbjects
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glfwTerminate();
	return 0;
}

void RenderSystem::AddToQueue(GraphicalObj* Obj) 
{
	RenderQueue.push_back(Obj);
}
