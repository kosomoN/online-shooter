#include "WindowSystem.h"
#include "GlobalSystem.h"
#include <stdio.h>
#include "Player.h"

CWindowSystem::~CWindowSystem()
{
	glfwTerminate();
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (gSys->pInput)
		gSys->pInput->key_callback(window, key, scancode, action, mods);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void CWindowSystem::init(int x, int y)
{
	if (!glfwInit())
		return;
	m_pWin = glfwCreateWindow(x, y, "DayZ 2", NULL, NULL);
	if (!m_pWin)
	{
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_pWin);
	glfwSetKeyCallback(m_pWin, key_callback);
	glfwSetFramebufferSizeCallback(m_pWin, framebuffer_size_callback);


	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}

	// Enable alpha
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void CWindowSystem::updateWindow()
{
	glfwSwapBuffers(m_pWin);
	glfwPollEvents();
}
