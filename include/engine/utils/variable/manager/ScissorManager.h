#pragma once

#include "Manager.h"
#include "..\datatype\Rectangle.h"

class MScissor
{
protected:
	static std::vector<Rect> m_unitList;
public:
	static void toggle();
	static Uint32 push(Rect& p_area, bool p_override = false);
	static Rect& pop();
};
