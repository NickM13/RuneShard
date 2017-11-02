#include "engine\game\world\entity\Entity.h"
#include "engine\game\world\World.h"

Entity::Entity() {

}
Entity::Entity(Vector3<GLfloat> p_position, Vector3<GLfloat> p_size, Vector3<GLfloat> p_rotation) {
	m_size = p_size;
	m_position = p_position;
	m_rotation = p_rotation;
	m_onGround = false;
}
Entity::~Entity() {

}

void Entity::push(Vector3<GLfloat> p_direction) {
	m_velocity = m_velocity + p_direction;
}
void Entity::move(Vector3<GLfloat> p_direction) {

}
void Entity::turn(Vector3<GLfloat> p_rotation) {

}

void Entity::input() {

}
void Entity::updatePhysics(WorldData p_world, GLfloat p_deltaTime) {

}
void Entity::updateCollision(WorldData p_world, GLfloat p_deltaTime) {

}
void Entity::update(WorldData p_world, GLfloat p_deltaTime) {
	while(m_rotation.y < 0)
		m_rotation.y += 360;
	m_rotation.y = fmod(m_rotation.y, 360);
	if(m_rotation.x < -90)
		m_rotation.x = -90;
	else if(m_rotation.x > 90)
		m_rotation.x = 90;
	updateCollision(p_world, p_deltaTime);
}
void Entity::render() {
	glPushMatrix();
	{
		glTranslatef(m_position.x, m_position.y, m_position.z);
		renderModel();
		renderOutline();
		renderShadow();
	}
	glPopMatrix();
}
void Entity::renderModel() {

}
void Entity::renderOutline() {
	if(GGameState::m_outline) {
		glBegin(GL_LINES);
		{
			glVertex3f(-m_size.x / 2, 0, -m_size.z / 2);
			glVertex3f(m_size.x / 2, 0, -m_size.z / 2);
			glVertex3f(m_size.x / 2, 0, -m_size.z / 2);
			glVertex3f(m_size.x / 2, 0, m_size.z / 2);
			glVertex3f(m_size.x / 2, 0, m_size.z / 2);
			glVertex3f(-m_size.x / 2, 0, m_size.z / 2);
			glVertex3f(-m_size.x / 2, 0, m_size.z / 2);
			glVertex3f(-m_size.x / 2, 0, -m_size.z / 2);

			glVertex3f(-m_size.x / 2, 0, -m_size.z / 2);
			glVertex3f(-m_size.x / 2, m_size.y, -m_size.z / 2);
			glVertex3f(m_size.x / 2, 0, -m_size.z / 2);
			glVertex3f(m_size.x / 2, m_size.y, -m_size.z / 2);
			glVertex3f(m_size.x / 2, 0, m_size.z / 2);
			glVertex3f(m_size.x / 2, m_size.y, m_size.z / 2);
			glVertex3f(-m_size.x / 2, 0, m_size.z / 2);
			glVertex3f(-m_size.x / 2, m_size.y, m_size.z / 2);

			glVertex3f(-m_size.x / 2, m_size.y, -m_size.z / 2);
			glVertex3f(m_size.x / 2, m_size.y, -m_size.z / 2);
			glVertex3f(m_size.x / 2, m_size.y, -m_size.z / 2);
			glVertex3f(m_size.x / 2, m_size.y, m_size.z / 2);
			glVertex3f(m_size.x / 2, m_size.y, m_size.z / 2);
			glVertex3f(-m_size.x / 2, m_size.y, m_size.z / 2);
			glVertex3f(-m_size.x / 2, m_size.y, m_size.z / 2);
			glVertex3f(-m_size.x / 2, m_size.y, -m_size.z / 2);
		}
		glEnd();
	}
}
void Entity::renderShadow() {
	/*
	glBindTexture(GL_TEXTURE_2D, 0);
	GLfloat _near;
	Sint8 _face;
	Vector2<Uint16> _max = Vector2<Uint16>(ceil(getCorner().x + getSize().x - 0.0001f) - floor(getCorner().x), ceil(getCorner().z + getSize().z - 0.0001f) - floor(getCorner().z));
	Vector4<GLfloat> _sqr;
	Vector3<GLfloat> _center = getCenter() + (getSize().ceil() / 2);

	for(Sint32 x = 0; x < _max.x; x++)
	{
		for(Sint32 z = 0; z < _max.y; z++)
		{
			glPushMatrix();
			{
				_near = 0;
				World::getInstance().castRay({x + floor(getCorner().x) + 0.5f, getPosition().y, z + floor(getCorner().z) + 0.5f}, {0.f, -10.f, 0.f}, _near, _face);

				if(_near < 1)
				{
					glTranslatef(x + floor(getCorner().x), getPosition().y - _near * 10 + 0.005f, z + floor(getCorner().z));
					glColor4f(0, 0, 0, (1.f - _near) * 0.15f);
					glBegin(GL_QUADS);
					{
						_sqr = Vector4<GLfloat>(x == 0 ? fmodf(getCorner().x, 1) : 0, z == 0 ? fmodf(getCorner().z, 1) : 0,
							x == _max.x - 1 ? fmodf(getCorner().x + getSize().x - 0.0001f, 1) : 1, z == _max.y - 1 ? fmodf(getCorner().z + getSize().z - 0.0001f, 1) : 1);

						glVertex3f(_sqr.x1, 0, _sqr.y1);
						glVertex3f(_sqr.x1, 0, _sqr.y2);
						glVertex3f(_sqr.x2, 0, _sqr.y2);
						glVertex3f(_sqr.x2, 0, _sqr.y1);
					}
					glEnd();
				}
			}
			glPopMatrix();
		}
	}
	*/
}
