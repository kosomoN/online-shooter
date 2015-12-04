#pragma once

#include <GL/glew.h>
#include <GLFW\glfw3.h>

class CWindowSystem
{
public:
	CWindowSystem() {};
	~CWindowSystem();
	void init(int x, int y);
	void updateWindow();
	bool shouldClose() { return glfwWindowShouldClose(m_pWin) != 0; }
	GLFWwindow* getWindowPtr() { return m_pWin; }
private:
	GLFWwindow* m_pWin;

};