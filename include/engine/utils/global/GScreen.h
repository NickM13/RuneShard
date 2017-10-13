#pragma once

#include "engine\utils\variable\datatype\Macros.h"
#include "engine\utils\variable\datatype\Vector2.h"
#include "engine\utils\OpenGL.h"
#include <vector>
#include <string>
#include <iostream>

class GScreen
{
public:
	static std::string m_tooltip;
	static float m_fps;
	static float m_fov;
	static float m_deltaTime;
	static Sint8 m_exitting;
	static bool m_developer;

	static GLFWwindow *m_window;
	static Vector2<Sint32> m_monitorSize;
	static Vector2<Sint32> m_windowPos;
	static Vector2<Sint32> m_screenSize;

	static enum WindowCommand
	{
		NONE = 0,
		CLOSE,
		RESIZE,
		MINIMIZE
	} m_windowCommand;

	static void initWindow(GLFWwindow *p_window);

	static void updateWindow();
};
