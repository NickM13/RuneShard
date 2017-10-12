#include "Application.h"

#include "engine\sfx\Sound.h"

int main(int* argcp, char** argv)
{
	Application::getInstance().init();
	Application::getInstance().run();
	Application::getInstance().close();

	return 0;
}
