#pragma once
#include "..\Entity.h"
#include "engine\game\world\entity\actor\ability\LAbility.h"

class Actor : public Entity {
public:
	enum Direction {
		FORWARD = 0,
		RIGHT = 1,
		BACK = 2,
		LEFT = 3
	};
protected:
	enum Race {
		HUMAN = 0,
		ORC = 1
	};
	enum Class {
		ADVENTURER,
		WARRIOR,
		MAGE
	};
	Uint32 m_id;
	std::string m_name;
	bool m_isSprinting;
	Uint8 m_maxAirJumps; // For double jumps
	Uint8 m_airJumps;
	GLfloat m_airJumpBurst; // Timer for moving faster after double jumping
	VoxelModel* m_voxelModel = 0;
	struct Bind {
		enum Hardware {
			MOUSE = 0,
			KEYBOARD = 1,
			OTHER = 2
		} hardware;
		Sint32 id;
		Bind(Hardware p_hardware = OTHER, Sint32 p_id = 0) : hardware(p_hardware), id(p_id) {};
		bool operator<(Bind p_cb) const {
			return (hardware < p_cb.hardware || (hardware == p_cb.hardware && (id < p_cb.id)));
		}
	};
	std::map<Bind, Ability*> m_abilityMap;
	struct Stats {
		GLfloat m_moveSpeed;
		GLfloat m_jumpHeight;
		GLfloat m_health, m_maxHealth;
		GLfloat m_mana, m_maxMana;
		GLfloat m_intellect;
	} m_stats;

	void updatePhysics(WorldData p_world, GLfloat p_deltaTime);
	virtual void updateCollision(WorldData p_world, GLfloat p_deltaTime);
	void renderModel();
public:
	Actor(Vector3<GLfloat> p_position, Vector3<GLfloat> p_size, Vector3<GLfloat> p_rotation);
	Actor(std::string p_fileName) {};
	~Actor() {};

	void setId(Uint32 p_id) { m_id = p_id; }
	Uint32 getId() { return m_id; }

	Actor* setModel(VoxelModel* p_voxelModel);

	Actor* setName(std::string p_name);
	Actor* setMoveSpeed(GLfloat p_moveSpeed);
	Actor* setJumpHeight(GLfloat p_jumpHeight);

	Actor* setPosition(Vector3<GLfloat> p_position) { m_position = p_position; return this; }
	Actor* setRotation(Vector3<GLfloat> p_rotation) { m_rotation = p_rotation; return this; }

	void setMovement(Vector3<GLfloat> p_direction);
	void setMovement(Direction p_direction);
	void addMovement(Vector3<GLfloat> p_direction);
	void addMovement(Direction p_direction);
	void turn(Vector3<GLfloat> p_rotation);
	void jump();
	void setSprinting(bool p_state) { m_isSprinting = p_state; }
	bool isSprinting() { return m_isSprinting; }

	void abilityInput();
	void abilityUpdate();
	void abilityRender();

	void update(WorldData p_world, GLfloat p_deltaTime);

	std::string getName() const { return m_name; }
	GLfloat getHealth() const { return m_health; };
	GLfloat getMaxHealth() const { return m_maxHealth; };
	void damage(GLfloat amt) { m_health -= amt; };
};

class MActor {
private:
	static std::vector<Actor*> m_actorList;
	static Uint32 m_actorCount;
public:
	static void addActor(Actor* p_actor);
	static void addActor(std::string p_fileName);
	static std::vector<Actor*> getActorList();
	static Actor* getActor(Uint32 p_id);
	static void input();
	static void update(WorldData &p_world, GLfloat p_updateTime);
	static void render();
};
