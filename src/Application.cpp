#include "Application.h"

Vector2<Uint16> Application::m_screenSize = {};
GLFWwindow* Application::m_mainWindow = 0;

bool Application::init() {
	m_maxFps = 60;
	m_screenSize = Vector2<Uint16>(1280, 768);
	GScreen::m_developer = true;
	GScreen::m_fps = 0;
	GScreen::m_screenSize = m_screenSize;
	GScreen::m_exitting = 0;
	GKey::init();
	if(!glfwInit())
		return false;
	if(!glewInit())
		return false;
	m_screenSize = GScreen::m_screenSize;
	glfwWindowHint(GLFW_RESIZABLE, false);
	m_mainWindow = glfwCreateWindow(m_screenSize.x, m_screenSize.y, "Voxel Engine Indev v0.1", 0, 0);
	glfwSetInputMode(m_mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if(!m_mainWindow) {
		glfwTerminate();
		return false;
	}
	glfwSetKeyCallback(m_mainWindow, keyCallback);
	glfwSetMouseButtonCallback(m_mainWindow, mousePressCallback);
	glfwSetCursorEnterCallback(m_mainWindow, mouseEnterCallback);
	glfwSetCursorPosCallback(m_mainWindow, mouseMovedCallback);
	glfwSetScrollCallback(m_mainWindow, mouseScrollCallback);
	glfwSetWindowSizeCallback(m_mainWindow, windowResizeCallback);
	glfwSetWindowPos(m_mainWindow, 320, 200);
	glfwMakeContextCurrent(m_mainWindow);
	glClearColor(0.35f, 0.25f, 0.95f, 1);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	m_game = new Game();
	return true;
}

void Application::close() {
	delete m_game;
}

void Application::keyCallback(GLFWwindow* p_window, int p_keycode, int p_scancode, int p_action, int p_mods) {
	//std::cout << p_keycode << " " << p_scancode << " " << p_action << " " << p_mods << "\n";
	GKey::keyEvent(p_keycode, p_scancode, p_action, p_mods);
	if(GKey::keyPressed('`')) GScreen::m_exitting = 2;
}

void Application::mousePressCallback(GLFWwindow* p_window, int p_button, int p_state, int p_mods) {
	GMouse::mouseEvent(p_button, p_state);
}

void Application::mouseMovedCallback(GLFWwindow* p_window, double p_x, double p_y) {
	GMouse::setMousePos(Vector2<Sint32>(Sint32(p_x - m_screenSize.x / 2), Sint32(p_y - m_screenSize.y / 2)));
}

void Application::mouseScrollCallback(GLFWwindow* p_window, double p_x, double p_y) {
	GMouse::addScroll(Sint8(p_y));
}

void Application::windowResizeCallback(GLFWwindow* p_window, int p_x, int p_y) {
	glfwSetWindowSize(p_window, m_screenSize.x, m_screenSize.y);
	//Globals::getInstance().m_screenSize = Vector2< Uint16 >(p_x, p_y);
	//m_screenSize = Vector2< Uint16 >(p_x, p_y);

	//glViewport(0, 0, m_screenSize.x, m_screenSize.y);

	//init2d();

	//Game::getInstance().resize();
}

void Application::mouseEnterCallback(GLFWwindow* p_window, int p_action) {}

void Application::init2d() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-m_screenSize.x / 2, m_screenSize.x / 2, m_screenSize.y / 2, -m_screenSize.y / 2, -2000.f, 2000.f);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glLoadIdentity();
}
void Application::init3d() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, GLfloat(m_screenSize.x) / m_screenSize.y, 0.01f, 2000.f);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glCullFace(GL_BACK);
	glLoadIdentity();
}

void Application::run() {
	GLdouble i;
	while(GScreen::m_exitting != 2) {
		i = glfwGetTime();
	#ifdef _DEBUG
		if(GKey::keyPressed('1')) DebugBreak();
	#endif
		input();
		update();
		render();
		m_sleepTime = DWORD(max(1000 / m_maxFps - ((glfwGetTime() - i) * 1000), 0));
		if(m_sleepTime > 0)
			Sleep(m_sleepTime);
		GScreen::m_fps = 1.f / GLfloat(glfwGetTime() - i);
	}
	glfwTerminate();
}

void Application::input() {
	if(glfwWindowShouldClose(m_mainWindow)) {
		glfwSetWindowShouldClose(m_mainWindow, false);
		GScreen::m_exitting = 1;
	}
	GKey::update();
	GMouse::update();
	glfwPollEvents();
	m_game->input();
}

void Application::update() {
	m_game->update();
}

void Application::render() {
	glLoadIdentity();
	init3d();
	m_game->render3d();
	init2d();
	m_game->render2d();
	glfwSwapBuffers(m_mainWindow);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
