#pragma once
#include "engine\utils\Utilities.h"
#include "..\entity\actor\Actor.h"

class Camera {
private:
	Actor *m_followActor;
	Vector3<GLfloat> m_position;
	Vector3<GLfloat> m_tRotation, m_rotation;
	GLfloat m_boomDistance;
	GLfloat m_tBoomDistance;
	const GLfloat MAX_BOOM = 100, MIN_BOOM = 2;
	const Vector3<GLfloat> _camSize = Vector3<GLfloat>(0.1f, 0.1f, 0.1f);
public:
	Camera();
	void followActor(Actor *p_actor);
	Actor* getActor() const { return m_followActor; }

	void setPosition(Vector3<GLfloat> p_position, bool p_hardset = false);
	void addPosition(Vector3<GLfloat> p_position, bool p_hardset = false);
	void setRotation(Vector3<GLfloat> p_position, bool p_hardset = false);
	void addRotation(Vector3<GLfloat> p_position, bool p_hardset = false);

	virtual void input();
	virtual void update(WorldData& p_worldData, GLfloat p_deltaTime);
	void useRotation();
	void useView();
};
