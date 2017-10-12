#include "engine\game\world\entity\Entity.h"
#include "engine\game\world\World.h"

Entity::Entity()
{

}
Entity::Entity(Vector3<GLfloat> p_position, Vector3<GLfloat> p_size, Vector3<GLfloat> p_rotation)
{
	m_size = p_size;
	m_position = p_position;
	m_rotation = p_rotation;
	setMoveSpeed(1);

	m_onGround = false;
}
Entity::~Entity()
{

}

void Entity::setModel(VoxelModel* p_voxelModel)
{
	m_voxelModel = p_voxelModel;
}

void Entity::setMoveSpeed(GLfloat p_speed)
{
	m_speed = p_speed;
}
void Entity::setJumpHeight(GLfloat p_jumpHeight)
{
	m_jumpHeight = sqrt(p_jumpHeight + 0.025f) / sqrt(5.f / GRAVITY);
}

void Entity::push(Vector3<GLfloat> p_direction)
{
	m_velocity = m_velocity + p_direction;
}
void Entity::move(Vector3<GLfloat> p_direction)
{

}
void Entity::turn(Vector3<GLfloat> p_rotation)
{

}
void Entity::jump()
{
	if(m_onGround || m_noClip)
	{
		m_velocity.y = m_jumpHeight;
	}
	else if(m_jumps > 0)
	{
		m_velocity.y = m_jumpHeight;
		m_jumps--;
	}
}

void Entity::input()
{

}

void Entity::update(WorldData p_world, GLfloat p_deltaTime)
{
	Vector3<GLfloat> _velocity = m_velocity;
	m_velocity.y -= p_deltaTime * GRAVITY;
	m_velocity.y = m_velocity.y + m_acceleration.y * (p_deltaTime * m_speed);
	if(m_onGround)
	{
		m_velocity.x = m_velocity.x + m_acceleration.x * (p_deltaTime * m_speed);
		m_velocity.z = m_velocity.z + m_acceleration.z * (p_deltaTime * m_speed);
		m_velocity.x /= 2.f;
		m_velocity.z /= 2.f;
	}
	else
	{
		m_velocity.x = m_velocity.x + m_acceleration.x * (p_deltaTime * m_speed / 5);
		m_velocity.z = m_velocity.z + m_acceleration.z * (p_deltaTime * m_speed / 5);
		m_velocity.x /= 1.1f;
		m_velocity.z /= 1.1f;
	}
	if(abs(m_velocity.x) < 0.0001f)
		m_velocity.x = 0;
	if(abs(m_velocity.z) < 0.0001f)
		m_velocity.z = 0;
	_velocity = ((_velocity + m_velocity) / 2) * (p_deltaTime * 10);

	if(Globals::getInstance().m_keyStates[GLFW_KEY_4] == 1)
		m_position.y = 20;

	GLfloat _near = 0;
	Sint8 _face = 0;
	if(m_noClip)
	{
		m_position = m_position + _velocity;
	}
	else
	{
		m_onGround = false;
		while(_velocity.getLength() > 0)
		{
			p_world.castBox(m_position - Vector3<GLfloat>(m_size.x / 2, 0, m_size.z / 2), m_size, _velocity, _near, _face);
			if(_near != 1)
			{
				m_position.x += _velocity.x * _near;
				m_position.y += _velocity.y * _near;
				m_position.z += _velocity.z * _near;
				_velocity = _velocity * (1.f - _near);
				if(_face & 1)
				{
					if(m_velocity.x < 0)
						m_position.x = roundf(m_position.x - m_size.x / 2) + m_size.x / 2;
					else
						m_position.x = roundf(m_position.x + m_size.x / 2) - m_size.x / 2;

					m_velocity.x = 0;
					_velocity.x = 0;
				}
				if(_face & 2)
				{
					if(m_velocity.y < 0)
					{
						m_position.y = roundf(m_position.y);
						m_onGround = true;
						m_jumps = m_airJumps;
					}
					else
						m_position.y = roundf(m_position.y) + (1.f - fmodf(m_size.y, 1));

					m_velocity.y = 0;
					_velocity.y = 0;
				}
				if(_face & 4)
				{
					if(m_velocity.z < 0)
						m_position.z = roundf(m_position.z - m_size.z / 2) + m_size.z / 2;
					else
						m_position.z = roundf(m_position.z + m_size.z / 2) - m_size.z / 2;

					m_velocity.z = 0;
					_velocity.z = 0;
				}
				
				_near = 0;
			}
			else
			{
				m_position.x += _velocity.x;
				m_position.y += _velocity.y;
				m_position.z += _velocity.z;
				_velocity = {};
			}
		}
	}
}

void Entity::render()
{
	glPushMatrix();
	{
		glColor3f(0.5f, 0.5f, 0.5f);
		glTranslatef(m_position.x, m_position.y, m_position.z);
		/*
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
		*/
		if(m_voxelModel)
		{
			glScalef(1.f / 16, 1.f / 16, 1.f / 16);
			m_voxelModel->render();
		}
	}
	glPopMatrix();
}
void Entity::renderShadow()
{
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

void Entity::useView()
{
	glRotatef(m_rotation.x, 1, 0, 0);
	glRotatef(m_rotation.y, 0, 1, 0);
	glRotatef(m_rotation.z, 0, 0, 1);
	glTranslatef(-(m_position.x), -(m_position.y + m_size.y - 0.15f), -(m_position.z));
}
