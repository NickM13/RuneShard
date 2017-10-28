#include "engine\gfx\gui\frequency\Graph.h"


CGraph::CGraph(std::string p_compName, std::string p_title, Vector2<Sint32> p_pos, Vector2<Sint32> p_size, Vector2<GLfloat> p_scale)
	: Component(p_compName, p_title, p_pos, p_size, ACTION) {
	m_scale = p_scale;
	m_points.push_back({0, 0});
};

void CGraph::addPoint(Vector2<GLfloat> p_point) {
	m_points.push_back(p_point);
}

void CGraph::input(Sint8& p_interactFlags) {

}
void CGraph::update(Vector2<Sint32> p_pos) {

}
void CGraph::render() {
	GLfloat _min = m_points[m_points.size() - 1].x - m_scale.x;
	renderBack();
	renderFill();
	glDisable(GL_MULTISAMPLE);
	glTranslatef(m_pos.x, m_pos.y, 0);
	MScissor::push(Rect(0, 0, m_size.x, m_size.y));
	glColor3f(1, 1, 1);
	glPushMatrix();
	{
		glTranslatef(0, m_size.y, 0);
		glScalef(1.f / (m_scale.x / m_size.x), -1.f / (m_scale.y / m_size.y), 1);
		glTranslatef(-_min, 0, 0);
		glColor3f(1, 1, 1);
		glBegin(GL_LINES);
		{
			for(Sint16 i = 0; i < Sint16(m_points.size()) - 1; i++) {
				if(m_points[i + 1].x >= _min) {
					glVertex2f(m_points[i].x, m_points[i].y);
					glVertex2f(m_points[i + 1].x, m_points[i + 1].y);
				}
			}
		}
		glEnd();
	}
	glPopMatrix();
	MScissor::pop();
	glEnable(GL_MULTISAMPLE);
}
