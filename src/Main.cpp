#include "Application.h"

int main(int* argcp, char** argv)
{
	if(Application::getInstance().init()) {
		Application::getInstance().run();
		Application::getInstance().close();
		return 0;
	}
	return 1;
}
