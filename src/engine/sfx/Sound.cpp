#include "engine\sfx\Sound.h"

Source::Source() {
	alGenSources(1, &m_sourceId);
}

void Source::setBuffer(ALuint p_bufferId) {
	alSourcei(m_sourceId, AL_BUFFER, p_bufferId);
}
void Source::setLooping(bool p_loop) {
	alSourcei(m_sourceId, AL_LOOPING, p_loop);
}
void Source::setPosition(Vector3<GLfloat> p_pos) {
	m_pos = p_pos;
	alSource3f(m_sourceId, AL_POSITION, m_pos.x, m_pos.y, m_pos.z);
}
void Source::setVelocity(Vector3<GLfloat> p_vel) {
	m_vel = p_vel;
	alSource3f(m_sourceId, AL_VELOCITY, m_vel.x, m_vel.y, m_vel.z);
}

void Source::play() {
	alSourcePlay(m_sourceId);
}
void Source::playAtListener() {
	Vector3<GLfloat> pos;
	alGetListenerfv(AL_POSITION, &pos.x);
	setPosition(pos);
	alSourcePlay(m_sourceId);
	setPosition(m_pos);
}



ALCdevice* Sound::m_device = 0;
ALCcontext* Sound::m_context = 0;
std::map<std::string, ALuint> Sound::m_bufferMap;

bool Sound::init() {
	alutInitWithoutContext(NULL, NULL);

	m_device = alcOpenDevice(NULL);
	if(m_device) {
		m_context = alcCreateContext(m_device, NULL);
		alcMakeContextCurrent(m_context);
	}

	return true;
}
void Sound::close() {
	m_context = alcGetCurrentContext();
	m_device = alcGetContextsDevice(m_context);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(m_context);
	alcCloseDevice(m_device);

	alutExit();
}

void Sound::setListenPosition(Vector3<GLfloat> p_pos) {
	alListener3f(AL_POSITION, p_pos.x, p_pos.y, p_pos.z);
}
void Sound::setListenVelocity(Vector3<GLfloat> p_vel) {
	alListener3f(AL_VELOCITY, p_vel.x, p_vel.y, p_vel.z);
}
void Sound::setListenOrientation(Vector3<GLfloat> p_lookAt) {
	ALfloat ori[] = {p_lookAt.x, p_lookAt.y, p_lookAt.z, 0, 1, 0};
	alListenerfv(AL_ORIENTATION, ori);
}

ALuint Sound::loadSoundFile(std::string p_soundName, std::string p_filename) {
	ALuint bufferId = alutCreateBufferFromFile(("res\\sound\\" + p_filename).c_str());
	ALint size, frequency, channels, bits;
	ALfloat samples, seconds;
	alGetBufferi(bufferId, AL_CHANNELS, &channels);
	alGetBufferi(bufferId, AL_SIZE, &size);
	alGetBufferi(bufferId, AL_BITS, &bits);
	alGetBufferi(bufferId, AL_FREQUENCY, &frequency);
	samples = size / ((bits / 8.f) * channels);
	seconds = (float)samples / (float)frequency;
	std::cout << seconds << std::endl;
	if(bufferId)
		m_bufferMap.insert({p_soundName, bufferId});
	return bufferId;
}
ALuint Sound::getSoundId(std::string p_soundName) {
	if(m_bufferMap.find(p_soundName) != m_bufferMap.end())
		return m_bufferMap[p_soundName];
	return 0;
}
