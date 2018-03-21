#pragma once

#include "LOpenAL.h"
#include "engine\utils\Singleton.h"
#include "engine\utils\Utilities.h"
#include <map>

//Stores buffer id, plays sound
class Source {
private:
	ALuint m_sourceId;
	ALuint m_bufferId;
	GLfloat m_bufferLength;
	Vector3<GLfloat> m_pos;
	Vector3<GLfloat> m_vel;
public:
	Source();
	
	void setBuffer(ALuint p_bufferId);
	void setLooping(bool p_loop);
	void setPosition(Vector3<GLfloat> p_pos);
	void setVelocity(Vector3<GLfloat> p_vel);

	void play();
	void playAtListener();
};

class Sound {
private:
	static ALCdevice* m_device;
	static ALCcontext* m_context;
	static std::map<std::string, ALuint> m_bufferMap;
public:
	static bool init();
	static void close();

	static void setListenPosition(Vector3<GLfloat>);
	static void setListenVelocity(Vector3<GLfloat>);
	static void setListenOrientation(Vector3<GLfloat> p_lookAt);

	// res\\sound\\p_filename
	static ALuint loadSoundFile(std::string p_soundName, std::string p_filename);
	static ALuint getSoundId(std::string p_soundName);
};
