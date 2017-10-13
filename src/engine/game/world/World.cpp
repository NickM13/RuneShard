#include "engine\game\world\World.h"
#include "engine\utils\Utilities.h"
#include "engine\utils\variable\manager\ColorManager.h"

#include <direct.h>

#include <iostream>

void World::init(Vector2<Sint32> p_worldSize) {
	m_skyTexture = MTexture::getTexture("Daylight Sky.png");
	//m_player = new Actor(Vector3<GLfloat>(p_worldSize.x * CHUNK_SIZE / 2, 25, p_worldSize.y * CHUNK_SIZE / 2), Vector3<GLfloat>(0.9f, 1.8f, 0.9f), Vector3<GLfloat>(0, 0, 0));
	m_player = new Actor(Vector3<GLfloat>(p_worldSize.x * CHUNK_SIZE / 2, 7, p_worldSize.y * CHUNK_SIZE / 2), Vector3<GLfloat>(0.9f, 1.8f, 0.9f), Vector3<GLfloat>(0, 0, 0));
	m_worldData.m_worldSize = Vector3<Sint32>(p_worldSize.x, 1, p_worldSize.y);
	m_worldData.m_chunkData = new std::vector<Chunk*>*[m_worldData.m_worldSize.x];
	for(Uint16 x = 0; x < m_worldData.m_worldSize.x; x++) {
		m_worldData.m_chunkData[x] = new std::vector<Chunk*>[m_worldData.m_worldSize.z];
		for(Uint16 y = 0; y < m_worldData.m_worldSize.z; y++)
			m_worldData.m_chunkData[x][y].push_back(new Chunk());
	}
	m_initialized = true;
}
void World::generate(Vector2<Sint32> p_worldSize) {

}
World::~World() {
	if(!m_initialized)
		return;
	for(Uint16 x = 0; x < m_worldData.m_worldSize.x; x++) {
		for(Uint16 y = 0; y < m_worldData.m_worldSize.z; y++) {
			m_worldData.m_chunkData[x][y].clear();
		}
		delete[] m_worldData.m_chunkData[x];
	}
	delete[] m_worldData.m_chunkData;
}

void World::setVoxel(Vector3<Sint32> p_pos, Uint32 p_voxel) {
	m_worldData.setVoxel(p_pos, p_voxel);
}
Voxel World::getVoxel(Vector3<Sint32> p_pos) {
	return m_worldData.getVoxel(p_pos);
}
Uint16 World::getVoxelId(Vector3<Sint32> p_pos) {
	return m_worldData.getVoxelId(p_pos);
}

void World::addChunk(Vector2<Sint32> p_chunk) {
	m_worldData.addChunk(p_chunk);
}

Actor* World::addActor(Actor* p_actor) {
	MActor::addActor(p_actor);
	return p_actor;
}

void World::input(Vector2<Sint32> p_mousePos) {
	m_player->turn(Vector3<GLfloat>(p_mousePos.y / 4.f, p_mousePos.x / 4.f, 0));
	Vector3<GLfloat> _dir;
	if(GKey::keyDown(GLFW_KEY_W)) {
		_dir.x += (Math::sind(m_player->getRotation().y));
		_dir.z -= (Math::cosd(m_player->getRotation().y));
	}
	if(GKey::keyDown(GLFW_KEY_A)) {
		_dir.x -= (Math::cosd(m_player->getRotation().y));
		_dir.z -= (Math::sind(m_player->getRotation().y));
	}
	if(GKey::keyDown(GLFW_KEY_S)) {
		_dir.x -= (Math::sind(m_player->getRotation().y));
		_dir.z += (Math::cosd(m_player->getRotation().y));
	}
	if(GKey::keyDown(GLFW_KEY_D)) {
		_dir.x += (Math::cosd(m_player->getRotation().y));
		_dir.z += (Math::sind(m_player->getRotation().y));
	}
	m_player->move(_dir);
	if(GKey::keyPressed(GLFW_KEY_SPACE))
		m_player->jump();

	MActor::input();
	MParticle::input();
}
void World::update(GLfloat p_deltaUpdate) {
	MActor::update(m_worldData, p_deltaUpdate);
	MParticle::update(m_worldData, p_deltaUpdate);
}
void World::render() {
	glPushMatrix();
	{
		renderSkyBox();
		m_player->useView();
		glBindTexture(GL_TEXTURE_2D, 0);
		for(Uint16 x = 0; x < m_worldData.m_worldSize.x; x++) {
			for(Uint16 z = 0; z < m_worldData.m_worldSize.z; z++) {
				for(Uint16 y = 0; y < m_worldData.m_chunkData[x][z].size(); y++) {
					glPushMatrix();
					{
						glTranslatef(GLfloat(x * CHUNK_SIZE), GLfloat(y * CHUNK_SIZE), GLfloat(z * CHUNK_SIZE));
						m_worldData.m_chunkData[x][z][y]->render();
					}
					glPopMatrix();
				}
			}
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		MActor::render();
		MParticle::render();
	}
	glPopMatrix();
}
void World::renderSkyBox() {
	glPushMatrix();
	{
		glRotatef(m_player->getRotation().x, 1, 0, 0);
		glRotatef(m_player->getRotation().y, 0, 1, 0);
		glRotatef(m_player->getRotation().z, 0, 0, 1);
		glBindTexture(GL_TEXTURE_2D, m_skyTexture->getId());
		glColor3f(1, 1, 1);
		glScalef(1024, 1024, 1024);
		Vector2<GLfloat> _c = Vector2<GLfloat>(1.f, 1.f) / m_skyTexture->getSize();
		GLfloat _t1 = 1.f / 3;
		GLfloat _t2 = 2.f / 3;
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.25f - _c.x, _t2 - _c.y); glVertex3f(-1, 1, -1);
			glTexCoord2f(0 + _c.x, _t2 - _c.y); glVertex3f(-1, 1, 1);
			glTexCoord2f(0 + _c.x, _t1 + _c.y); glVertex3f(-1, -1, 1);
			glTexCoord2f(0.25f - _c.x, _t1 + _c.y); glVertex3f(-1, -1, -1);

			glTexCoord2f(0.25f + _c.x, _t2 - _c.y); glVertex3f(-1, 1, -1);
			glTexCoord2f(0.25f + _c.x, _t1 + _c.y); glVertex3f(-1, -1, -1);
			glTexCoord2f(0.5f - _c.x, _t1 + _c.y); glVertex3f(1, -1, -1);
			glTexCoord2f(0.5f - _c.x, _t2 - _c.y); glVertex3f(1, 1, -1);

			glTexCoord2f(0.5f + _c.x, _t2 - _c.y); glVertex3f(1, 1, -1);
			glTexCoord2f(0.5f + _c.x, _t1 + _c.y); glVertex3f(1, -1, -1);
			glTexCoord2f(0.75f - _c.x, _t1 + _c.y); glVertex3f(1, -1, 1);
			glTexCoord2f(0.75f - _c.x, _t2 - _c.y); glVertex3f(1, 1, 1);

			glTexCoord2f(1 - _c.x, _t2 - _c.y); glVertex3f(-1, 1, 1);
			glTexCoord2f(0.75f + _c.x, _t2 - _c.y); glVertex3f(1, 1, 1);
			glTexCoord2f(0.75f + _c.x, _t1 + _c.y); glVertex3f(1, -1, 1);
			glTexCoord2f(1 - _c.x, _t1 + _c.y); glVertex3f(-1, -1, 1);

			glTexCoord2f(0.25f + _c.x, 1 - _c.y); glVertex3f(-1, 1, 1);
			glTexCoord2f(0.25f + _c.x, _t2 + _c.y); glVertex3f(-1, 1, -1);
			glTexCoord2f(0.5f - _c.x, _t2 + _c.y); glVertex3f(1, 1, -1);
			glTexCoord2f(0.5f - _c.x, 1 - _c.y); glVertex3f(1, 1, 1);

			glTexCoord2f(0.25f + _c.x, _t1 - _c.y); glVertex3f(-1, -1, -1);
			glTexCoord2f(0.25f + _c.x, 0 + _c.y); glVertex3f(-1, -1, 1);
			glTexCoord2f(0.5f - _c.x, 0 + _c.y); glVertex3f(1, -1, 1);
			glTexCoord2f(0.5f - _c.x, _t1 - _c.y); glVertex3f(1, -1, -1);
		}
		glEnd();
	}
	glPopMatrix();
}

void World::save(std::string p_worldName)
{
	// vmf = Voxel Map File
	std::cout << "map\\" << p_worldName << "\\terrain.vmf" << std::endl;
	std::ofstream _file;
	_mkdir(std::string("map").c_str());
	_mkdir(std::string("map\\" + p_worldName).c_str());

	_file.open(std::string("map\\" + p_worldName + "\\terrain.vmf"), std::ios::binary);
	{
		// Info
		FileExt::writeShort(_file, m_worldData.m_worldSize.x);
		FileExt::writeShort(_file, m_worldData.m_worldSize.z);

		/*
		std::vector<Voxel> _voxelTypes = MVoxel::getInstance().getUnitList();
		Color _color;

		// Voxel Definitions
		FileExt::writeShort(_file, Uint16(_voxelTypes.size()));
		for(Uint16 i = 0; i < _voxelTypes.size(); i++)
		{
			_color = MColor::getColor(_voxelTypes[i].color);
			FileExt::writeChar(_file, _voxelTypes[i].interactionType);

			FileExt::writeShort(_file, Uint16(_color.r * 2048));
			FileExt::writeShort(_file, Uint16(_color.g * 2048));
			FileExt::writeShort(_file, Uint16(_color.b * 2048));
			FileExt::writeShort(_file, Uint16(_color.a * 2048));
		}
		*/

		// World Data

		Uint16 _voxelId = getVoxelId({});
		Uint16 _voxelCount = 0;
		for(Sint16 y = 0; y < m_worldData.m_worldSize.y * CHUNK_SIZE; y++)
		{
			for(Sint16 x = 0; x < m_worldData.m_worldSize.x * CHUNK_SIZE; x++)
			{
				for(Sint16 z = 0; z < m_worldData.m_worldSize.z * CHUNK_SIZE; z++)
				{
					if(_voxelId != getVoxelId({x, y, z}) || _voxelCount >= 32766)
					{
						FileExt::writeShort(_file, _voxelId);
						FileExt::writeShort(_file, _voxelCount);

						_voxelId = getVoxelId({x, y, z});
						_voxelCount = 0;
					}
					_voxelCount++;
				}
			}
		}
		if(_voxelCount > 0)
		{
			FileExt::writeShort(_file, _voxelId);
			FileExt::writeShort(_file, _voxelCount);
		}
	}
	_file.close();
}

void World::load(std::string p_worldName)
{
	std::ifstream _file;

	Uint32 _length, _index;
	char* _data;

	_file.open(std::string("map\\" + p_worldName + "\\terrain.vmf").c_str(), std::ios::binary);
	{
		if(!_file.good())
		{
			std::cout << "Error: File \"map\\" << p_worldName << "\\terrain.vmf\" not found." << std::endl;
			_file.close();
			return;
		}

		_index = 0;

		_file.seekg(0, _file.end);
		_length = Uint32(_file.tellg());
		_file.seekg(0, _file.beg);
		_data = new char[_length];
		_file.read(_data, _length);

		m_worldData.m_worldSize.x = FileExt::readShort(_data, _index);
		m_worldData.m_worldSize.z = FileExt::readShort(_data, _index);

		init(Vector2<Sint32>(m_worldData.m_worldSize.x, m_worldData.m_worldSize.z));

		Uint16 _numOfVoxels = FileExt::readShort(_data, _index);
		//Sint8 _interactionType;
		//GLfloat r, g, b, a;
		/*
		MVoxel::getInstance().getUnitList().clear();
		for(Uint16 i = 0; i < _numOfVoxels; i++)
		{
			_interactionType = FileExt::readChar(_data, _index);
			r = FileExt::readShort(_data, _index) / 2048.f;
			g = FileExt::readShort(_data, _index) / 2048.f;
			b = FileExt::readShort(_data, _index) / 2048.f;
			a = FileExt::readShort(_data, _index) / 2048.f;
			MVoxel::getInstance().addUnit(Voxel(_interactionType, MColor::getInstance().getUnitID(Color(r, g, b, a))));
		}
		*/

		Uint16 x, y, z;
		x = y = z = 0;
		Uint16 _voxelCount;
		Voxel _voxel;
		bool _done = true;

		while(_done)
		{
			_voxel = MVoxel::getVoxel(FileExt::readShort(_data, _index));
			_voxelCount = FileExt::readShort(_data, _index);
			for(Uint16 i = 0; i < _voxelCount; i++)
			{
				if(_voxel.interactionType != 0)
				//setVoxel(Vector3<Sint32>(x, y, z), _voxel);
				x++;
				if(x >= m_worldData.m_worldSize.x * CHUNK_SIZE)
				{
					x = 0;
					z++;
					if(z >= m_worldData.m_worldSize.z * CHUNK_SIZE)
					{
						z = 0;
						y++;
						if(y >= m_worldData.m_worldSize.y * CHUNK_SIZE)
						{
							_done = false;
							break;
						}
					}
				}
			}
		}

		delete[] _data;
	}
	_file.close();
}
