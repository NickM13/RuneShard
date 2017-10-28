#pragma once

#include "engine\utils\Utilities.h"
#include "..\Component.h"
#include "engine\gfx\font\Font.h"

struct CGraph : public Component
{
private:
	Sint32 m_length;
	Sint32 m_maxValue;
	Sint32 m_slideValue;
	Sint8 m_width;
	Vector2<GLfloat> m_scale;

	bool m_held = false;
	Vector2<Sint32> m_holdPos;

	std::vector<Vector2<GLfloat>> m_points;
public:
	CGraph(std::string p_compName, std::string p_title, Vector2<Sint32> p_pos, Vector2<Sint32> p_size, Vector2<GLfloat> p_scale);

	void addPoint(Vector2<GLfloat> p_point);

	void input(Sint8& p_interactFlags);
	void update(Vector2<Sint32> p_pos);
	void render();
};
