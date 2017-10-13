#pragma once
#include "engine\game\Game.h"

class Application : public Singleton<Application>
{
public:
	bool init();
	void run();
	void close();
private:
	static GLFWwindow * m_mainWindow;
	static Vector2<Uint16> m_screenSize;
	Game* m_game;

	time_t m_maxFps = 60;
	DWORD m_sleepTime;


	static void keyCallback(GLFWwindow*, int, int, int, int);
	static void mousePressCallback(GLFWwindow*, int, int, int);
	static void mouseMovedCallback(GLFWwindow*, double, double);
	static void mouseScrollCallback(GLFWwindow*, double, double);
	static void windowResizeCallback(GLFWwindow*, int, int);
	static void mouseEnterCallback(GLFWwindow*, int);

	static void init2d();
	static void init3d();

	void input();
	void update();
	void render();
};
