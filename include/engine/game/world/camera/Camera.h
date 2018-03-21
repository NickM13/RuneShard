#pragma once
#include "engine\utils\Utilities.h"
#include "..\entity\actor\Actor.h"
#include "hud\HUD.h"

class Camera {
private:
	Actor *m_followActor;
	Vector3<GLfloat> m_tPosition, m_position;
	Vector3<GLfloat> m_velocity;
	Vector2<GLfloat> m_acceleration;
	Vector3<GLfloat> m_tRotation, m_rotation;
	GLfloat m_boomDistance;
	GLfloat m_tBoomDistance;
	const GLfloat MAX_BOOM = 20, MIN_BOOM = 0;
	const Vector3<GLfloat> _camSize = Vector3<GLfloat>(0.1f, 0.1f, 0.1f);

	HUD* m_hud;
public:
	Camera();
	void followActor(Actor *p_actor);
	Actor* getActor() const { return m_followActor; }

	void setPosition(Vector3<GLfloat> p_position, bool p_hardset = false);
	void addPosition(Vector3<GLfloat> p_position, bool p_hardset = false);
	void setRotation(Vector3<GLfloat> p_position, bool p_hardset = false);
	void addRotation(Vector3<GLfloat> p_position, bool p_hardset = false);

	Vector3<GLfloat> getPosition() const { return m_position; }
	Vector3<GLfloat> getRotation() const { return m_rotation; }

	void input();
	void update(WorldData& p_worldData, GLfloat p_deltaTime);
	void render2d();
	void useRotation();
	void useView();
};
