#pragma once

#include "engine\gfx\gui\frequency\Graph.h"

class DebugUI {
private:
	static CGraph* m_graph1;
	static CGraph* m_graph2;
	static CGraph* m_graph3;
public:
	static void init();
	static CGraph* getGraph1() { return m_graph1; }
	static CGraph* getGraph2() { return m_graph2; }
	static CGraph* getGraph3() { return m_graph3; }
};
