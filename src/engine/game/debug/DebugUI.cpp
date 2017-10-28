#include "engine\game\debug\DebugUI.h"

CGraph *DebugUI::m_graph1 = 0;
CGraph *DebugUI::m_graph2 = 0;
CGraph *DebugUI::m_graph3 = 0;

void DebugUI::init() {
	m_graph1 = new CGraph("GRAPH_DEBUG1", "Debug Graph 1", {100, 100}, {400, 300}, {10, 100});
	m_graph2 = new CGraph("GRAPH_DEBUG2", "Debug Graph 2", {100, 450}, {400, 300}, {10, 100});
	m_graph3 = new CGraph("GRAPH_DEBUG3", "Debug Graph 3", {100, 700}, {400, 300}, {10, 100});
}
