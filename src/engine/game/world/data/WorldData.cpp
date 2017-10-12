#include "engine\game\world\data\WorldData.h"

void WorldData::setVoxel(Vector3<Sint32> p_pos, Voxel p_voxel)
{
	Vector3<Sint32> _pos = Vector3<Sint32>((Vector3<GLfloat>(p_pos) / CHUNK_SIZE).floor());
	while(_pos.y > Sint32(m_chunkData[_pos.x][_pos.z].size()) - 1)
		addChunk({_pos.x, _pos.z});
	m_chunkData[_pos.x][_pos.z][_pos.y]->setVoxel(p_pos % CHUNK_SIZE, p_voxel);

	// Sides
	if(p_pos.x % CHUNK_SIZE == 0 && p_pos.x / CHUNK_SIZE > 0) // {-1, 0, 0}
	{
		while(_pos.y > Sint32(m_chunkData[_pos.x - 1][_pos.z].size()) - 1)
			addChunk({_pos.x - 1, _pos.z});
		m_chunkData[_pos.x - 1][_pos.z][_pos.y]->setVoxel({CHUNK_SIZE, p_pos.y % CHUNK_SIZE, p_pos.z % CHUNK_SIZE}, p_voxel);


		if(p_pos.y % CHUNK_SIZE == 0 && p_pos.y / CHUNK_SIZE > 0) // {-1, -1, 0}
		{
			m_chunkData[_pos.x - 1][_pos.z][_pos.y - 1]->setVoxel({CHUNK_SIZE, CHUNK_SIZE, p_pos.z % CHUNK_SIZE}, p_voxel);


			if(p_pos.z % CHUNK_SIZE == 0 && p_pos.z / CHUNK_SIZE > 0) // {-1, -1, -1}
			{
				while(_pos.y - 1 > Sint32(m_chunkData[_pos.x - 1][_pos.z - 1].size()) - 1)
					addChunk({_pos.x - 1, _pos.z - 1});
				m_chunkData[_pos.x - 1][_pos.z - 1][_pos.y - 1]->setVoxel({CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE}, p_voxel);
			}
			else if(p_pos.z % CHUNK_SIZE == CHUNK_SIZE - 1 && p_pos.z / CHUNK_SIZE < m_worldSize.x - 1) // {-1, -1, 1}
			{
				while(_pos.y - 1 > Sint32(m_chunkData[_pos.x - 1][_pos.z + 1].size()) - 1)
					m_chunkData[_pos.x - 1][_pos.z + 1][_pos.y - 1]->setVoxel({CHUNK_SIZE, CHUNK_SIZE, -1}, p_voxel);
			}
		}
		else if(p_pos.y % CHUNK_SIZE == CHUNK_SIZE - 1 && p_pos.y / CHUNK_SIZE < m_worldSize.z - 1) // {-1, 1, 0}
		{
			if(p_pos.y >= Sint32(m_chunkData[_pos.x - 1][_pos.z].size() * CHUNK_SIZE) - 1)
				addChunk({_pos.x - 1, _pos.z});
			m_chunkData[_pos.x - 1][_pos.z][_pos.y + 1]->setVoxel({CHUNK_SIZE, -1, p_pos.z % CHUNK_SIZE}, p_voxel);


			if(p_pos.z % CHUNK_SIZE == 0 && p_pos.z / CHUNK_SIZE > 0) // {-1, 1, -1}
			{
				while(_pos.y + 1 > Sint32(m_chunkData[_pos.x - 1][_pos.z - 1].size()) - 1)
					addChunk({_pos.x - 1, _pos.z - 1});
				m_chunkData[_pos.x - 1][_pos.z - 1][_pos.y + 1]->setVoxel({CHUNK_SIZE, -1, CHUNK_SIZE}, p_voxel);
			}
			else if(p_pos.z % CHUNK_SIZE == CHUNK_SIZE - 1 && p_pos.z / CHUNK_SIZE < m_worldSize.x - 1) // {-1, 1, 1}
			{
				while(_pos.y + 1 > Sint32(m_chunkData[_pos.x - 1][_pos.z + 1].size()) - 1)
					addChunk({_pos.x - 1, _pos.z + 1});
				m_chunkData[_pos.x - 1][_pos.z + 1][_pos.y + 1]->setVoxel({CHUNK_SIZE, -1, -1}, p_voxel);
			}
		}

		if(p_pos.z % CHUNK_SIZE == 0 && p_pos.z / CHUNK_SIZE > 0) // {-1, 0, -1}
		{
			while(_pos.y > Sint32(m_chunkData[_pos.x - 1][_pos.z - 1].size()) - 1)
				addChunk({_pos.x - 1, _pos.z - 1});
			m_chunkData[_pos.x - 1][_pos.z - 1][_pos.y]->setVoxel({CHUNK_SIZE, p_pos.y % CHUNK_SIZE, CHUNK_SIZE}, p_voxel);
		}
		else if(p_pos.z % CHUNK_SIZE == CHUNK_SIZE - 1 && p_pos.z / CHUNK_SIZE < m_worldSize.x - 1) // {-1, 0, 1}
		{
			while(_pos.y > Sint32(m_chunkData[_pos.x - 1][_pos.z + 1].size()) - 1)
				addChunk({_pos.x - 1, _pos.z + 1});
			m_chunkData[_pos.x - 1][_pos.z + 1][_pos.y]->setVoxel({CHUNK_SIZE, p_pos.y % CHUNK_SIZE, -1}, p_voxel);
		}
	}
	else if(p_pos.x % CHUNK_SIZE == CHUNK_SIZE - 1 && p_pos.x / CHUNK_SIZE < m_worldSize.x - 1) // {1, 0, 0}
	{
		while(_pos.y > Sint32(m_chunkData[_pos.x + 1][_pos.z].size()) - 1)
			addChunk({_pos.x + 1, _pos.z});
		m_chunkData[_pos.x + 1][_pos.z][_pos.y]->setVoxel({-1, p_pos.y % CHUNK_SIZE, p_pos.z % CHUNK_SIZE}, p_voxel);


		if(p_pos.y % CHUNK_SIZE == 0 && p_pos.y / CHUNK_SIZE > 0) // {1, -1, 0}
		{
			m_chunkData[_pos.x + 1][_pos.z][_pos.y - 1]->setVoxel({-1, CHUNK_SIZE, p_pos.z % CHUNK_SIZE}, p_voxel);


			if(p_pos.z % CHUNK_SIZE == 0 && p_pos.z / CHUNK_SIZE > 0) // {1, -1, -1}
			{
				while(_pos.y - 1 > Sint32(m_chunkData[_pos.x + 1][_pos.z - 1].size()) - 1)
					addChunk({_pos.x + 1, _pos.z - 1});
				m_chunkData[_pos.x + 1][_pos.z - 1][_pos.y - 1]->setVoxel({-1, CHUNK_SIZE, CHUNK_SIZE}, p_voxel);
			}
			else if(p_pos.z % CHUNK_SIZE == CHUNK_SIZE - 1 && p_pos.z / CHUNK_SIZE < m_worldSize.x - 1) // {1, -1, 1}
			{
				while(_pos.y - 1 > Sint32(m_chunkData[_pos.x + 1][_pos.z + 1].size()) - 1)
					addChunk({_pos.x + 1, _pos.z + 1});
				m_chunkData[_pos.x + 1][_pos.z + 1][_pos.y - 1]->setVoxel({-1, CHUNK_SIZE, -1}, p_voxel);
			}
		}
		else if(p_pos.y % CHUNK_SIZE == CHUNK_SIZE - 1 && p_pos.y / CHUNK_SIZE < m_worldSize.z - 1) // {1, 1, 0}
		{
			if(p_pos.y >= Sint32(m_chunkData[_pos.x + 1][_pos.z].size() * CHUNK_SIZE) - 1)
				addChunk({_pos.x + 1, _pos.z});
			m_chunkData[_pos.x + 1][_pos.z][_pos.y + 1]->setVoxel({-1, -1, p_pos.z % CHUNK_SIZE}, p_voxel);


			if(p_pos.z % CHUNK_SIZE == 0 && p_pos.z / CHUNK_SIZE > 0) // {1, 1, -1}
			{
				while(_pos.y + 1 > Sint32(m_chunkData[_pos.x + 1][_pos.z - 1].size()) - 1)
					addChunk({_pos.x + 1, _pos.z - 1});
				m_chunkData[_pos.x + 1][_pos.z - 1][_pos.y + 1]->setVoxel({-1, -1, CHUNK_SIZE}, p_voxel);
			}
			else if(p_pos.z % CHUNK_SIZE == CHUNK_SIZE - 1 && p_pos.z / CHUNK_SIZE < m_worldSize.x - 1) // {1, 1, 1}
			{
				while(_pos.y + 1 > Sint32(m_chunkData[_pos.x + 1][_pos.z + 1].size()) - 1)
					addChunk({_pos.x + 1, _pos.z + 1});
				m_chunkData[_pos.x + 1][_pos.z + 1][_pos.y + 1]->setVoxel({-1, -1, -1}, p_voxel);
			}
		}

		if(p_pos.z % CHUNK_SIZE == 0 && p_pos.z / CHUNK_SIZE > 0) // {1, 0, -1}
		{
			while(_pos.y > Sint32(m_chunkData[_pos.x + 1][_pos.z - 1].size()) - 1)
				addChunk({_pos.x + 1, _pos.z - 1});
			m_chunkData[_pos.x + 1][_pos.z - 1][_pos.y]->setVoxel({-1, p_pos.y % CHUNK_SIZE, CHUNK_SIZE}, p_voxel);
		}
		else if(p_pos.z % CHUNK_SIZE == CHUNK_SIZE - 1 && p_pos.z / CHUNK_SIZE < m_worldSize.x - 1) // {1, 0, 1}
		{
			while(_pos.y > Sint32(m_chunkData[_pos.x + 1][_pos.z + 1].size()) - 1)
				addChunk({_pos.x + 1, _pos.z + 1});
			m_chunkData[_pos.x + 1][_pos.z + 1][_pos.y]->setVoxel({-1, p_pos.y % CHUNK_SIZE, -1}, p_voxel);
		}
	}

	if(p_pos.y % CHUNK_SIZE == 0 && p_pos.y / CHUNK_SIZE > 0) // {0, -1, 0}
	{
		m_chunkData[_pos.x][_pos.z][_pos.y - 1]->setVoxel({p_pos.x % CHUNK_SIZE, CHUNK_SIZE, p_pos.z % CHUNK_SIZE}, p_voxel);


		if(p_pos.z % CHUNK_SIZE == 0 && p_pos.z / CHUNK_SIZE > 0) // {0, -1, -1}
		{
			while(_pos.y - 1 > Sint32(m_chunkData[_pos.x][_pos.z - 1].size()) - 1)
				addChunk({_pos.x, _pos.z - 1});
			m_chunkData[_pos.x][_pos.z - 1][_pos.y - 1]->setVoxel({p_pos.x % CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE}, p_voxel);
		}
		else if(p_pos.z % CHUNK_SIZE == CHUNK_SIZE - 1 && p_pos.z / CHUNK_SIZE < m_worldSize.x - 1) // {0, -1, 1}
		{
			while(_pos.y - 1 > Sint32(m_chunkData[_pos.x][_pos.z + 1].size()) - 1)
				addChunk({_pos.x, _pos.z + 1});
			m_chunkData[_pos.x][_pos.z + 1][_pos.y - 1]->setVoxel({p_pos.x % CHUNK_SIZE, CHUNK_SIZE, -1}, p_voxel);
		}
	}
	else if(p_pos.y % CHUNK_SIZE == CHUNK_SIZE - 1 && p_pos.y / CHUNK_SIZE < m_worldSize.z - 1) // {0, 1, 0}
	{
		if(p_pos.y >= Sint32(m_chunkData[_pos.x][_pos.z].size() * CHUNK_SIZE) - 1)
			addChunk({_pos.x, _pos.z});
		m_chunkData[_pos.x][_pos.z][_pos.y + 1]->setVoxel({p_pos.x % CHUNK_SIZE, -1, p_pos.z % CHUNK_SIZE}, p_voxel);


		if(p_pos.z % CHUNK_SIZE == 0 && p_pos.z / CHUNK_SIZE > 0) // {0, 1, -1}
		{
			while(_pos.y + 1 > Sint32(m_chunkData[_pos.x][_pos.z - 1].size()) - 1)
				addChunk({_pos.x, _pos.z - 1});
			m_chunkData[_pos.x][_pos.z - 1][_pos.y + 1]->setVoxel({p_pos.x % CHUNK_SIZE, -1, CHUNK_SIZE}, p_voxel);
		}
		else if(p_pos.z % CHUNK_SIZE == CHUNK_SIZE - 1 && p_pos.z / CHUNK_SIZE < m_worldSize.x - 1) // {0, 1, 1}
		{
			while(_pos.y + 1 > Sint32(m_chunkData[_pos.x][_pos.z + 1].size()) - 1)
				addChunk({_pos.x, _pos.z + 1});
			m_chunkData[_pos.x][_pos.z + 1][_pos.y + 1]->setVoxel({p_pos.x % CHUNK_SIZE, -1, -1}, p_voxel);
		}
	}

	if(p_pos.z % CHUNK_SIZE == 0 && p_pos.z / CHUNK_SIZE > 0) // {0, 0, -1}
	{
		while(_pos.y > Sint32(m_chunkData[_pos.x][_pos.z - 1].size()) - 1)
			addChunk({_pos.x, _pos.z - 1});
		m_chunkData[_pos.x][_pos.z - 1][_pos.y]->setVoxel({p_pos.x % CHUNK_SIZE, p_pos.y % CHUNK_SIZE, CHUNK_SIZE}, p_voxel);
	}
	else if(p_pos.z % CHUNK_SIZE == CHUNK_SIZE - 1 && p_pos.z / CHUNK_SIZE < m_worldSize.x - 1) // {0, 0, 1}
	{
		while(_pos.y > Sint32(m_chunkData[_pos.x][_pos.z + 1].size()) - 1)
			addChunk({_pos.x, _pos.z + 1});
		m_chunkData[_pos.x][_pos.z + 1][_pos.y]->setVoxel({p_pos.x % CHUNK_SIZE, p_pos.y % CHUNK_SIZE, -1}, p_voxel);
	}
}
Voxel WorldData::getVoxel(Vector3<Sint32> p_pos)
{
	Vector3<Sint32> _pos = Vector3<Sint32>((Vector3<GLfloat>(p_pos) / CHUNK_SIZE).floor());
	return m_chunkData[_pos.x][_pos.z][_pos.y]->getVoxel(p_pos % CHUNK_SIZE);
}
Uint16 WorldData::getVoxelId(Vector3<Sint32> p_pos)
{
	Vector3<Sint32> _pos = Vector3<Sint32>((Vector3<GLfloat>(p_pos) / CHUNK_SIZE).floor());
	return m_chunkData[_pos.x][_pos.z][_pos.y]->getVoxelId(p_pos % CHUNK_SIZE);
}

void WorldData::addChunk(Vector2<Sint32> p_chunk)
{
	m_chunkData[p_chunk.x][p_chunk.y].push_back(new Chunk());
	if(Sint32(m_chunkData[p_chunk.x][p_chunk.y].size()) > m_worldSize.y)
		m_worldSize.y = m_chunkData[p_chunk.x][p_chunk.y].size();
}

void WorldData::castRay(Vector3<GLfloat> p_start, Vector3<GLfloat> p_direction, GLfloat &p_near, Sint8 &p_face)
{
	GLfloat _near = p_near, _far = 1;
	Sint8 _side = 0;
	Math::castRay3d(p_start, p_direction, p_start.floor(), {1, 1, 1}, _near, _far, _side);
	Vector3<GLfloat> _floor;
	do
	{
		_floor = (p_start + p_direction * _near).floor();

		if(!(_floor.x < 0 || _floor.y < 0 || _floor.z < 0 || _floor.x >= m_worldSize.x * CHUNK_SIZE || _floor.z >= m_worldSize.z * CHUNK_SIZE ||
			_floor.y >= m_chunkData[Sint32(floor(_floor.x / CHUNK_SIZE))][Sint32(floor(_floor.z / CHUNK_SIZE))].size() * CHUNK_SIZE) &&
			_side != 0 && getVoxel(_floor).interactionType != 0)
		{
			p_face = _side;
			p_near = _near;
			return;
		}
		_near = _far + 0.0001f;
		_far = 1;
		Math::castRay3d(p_start, p_direction, (p_start + p_direction * _near).floor(), {1, 1, 1}, _near, _far, _side);
	} while(_near < 1 && _far > _near);
	p_face = 0;
	p_near = 1;
}
void WorldData::castBox(Vector3<GLfloat> p_start, Vector3<GLfloat> p_dimension, Vector3<GLfloat> p_direction, GLfloat &p_near, Sint8 &p_face)
{
	GLfloat _near = 1, _nearCast;
	Sint8 _side = 0, _sideCast;

	GLfloat _c = 0.0001f; // Slight offset for corners to cast from
	GLfloat _dX = p_dimension.x / ceil(p_dimension.x) - _c * 2;
	GLfloat _dY = p_dimension.y / ceil(p_dimension.y) - _c * 2;
	GLfloat _dZ = p_dimension.z / ceil(p_dimension.z) - _c * 2;

	if(p_direction.x < 0)
	{
		for(Uint16 y = 0; y <= ceil(p_dimension.y); y++)
		{
			for(Uint16 z = 0; z <= ceil(p_dimension.z); z++)
			{
				_nearCast = 0;
				_sideCast = 0;
				castRay(p_start + Vector3<GLfloat>(-_c, y * _dY + _c, z * _dZ + _c), p_direction, _nearCast, _sideCast);
				if((_nearCast < _near) && (_sideCast & 1))
				{
					_side = 1;
					_near = _nearCast;
				}
			}
		}
	}
	if(p_direction.x > 0)
	{
		for(Uint16 y = 0; y <= ceil(p_dimension.y); y++)
		{
			for(Uint16 z = 0; z <= ceil(p_dimension.z); z++)
			{
				_nearCast = 0;
				_sideCast = 0;
				castRay(p_start + Vector3<GLfloat>(p_dimension.x + _c, y * _dY + _c, z * _dZ + _c), p_direction, _nearCast, _sideCast);
				if((_nearCast < _near) && (_sideCast & 1))
				{
					_side = 1;
					_near = _nearCast;
				}
			}
		}
	}


	if(p_direction.y < 0)
	{
		for(Uint16 x = 0; x <= ceil(p_dimension.x); x++)
		{
			for(Uint16 z = 0; z <= ceil(p_dimension.z); z++)
			{
				_nearCast = 0;
				_sideCast = 0;
				castRay(p_start + Vector3<GLfloat>(x * _dX + _c, -_c, z * _dZ + _c), p_direction, _nearCast, _sideCast);
				if((_nearCast < _near) && (_sideCast & 2))
				{
					_side = 2;
					_near = _nearCast;
				}
			}
		}
	}
	if(p_direction.y > 0)
	{
		for(Uint16 x = 0; x <= ceil(p_dimension.x); x++)
		{
			for(Uint16 z = 0; z <= ceil(p_dimension.z); z++)
			{
				_nearCast = 0;
				_sideCast = 0;
				castRay(p_start + Vector3<GLfloat>(x * _dX + _c, p_dimension.y + _c, z * _dZ + _c), p_direction, _nearCast, _sideCast);
				if((_nearCast < _near) && (_sideCast & 2))
				{
					_side = 2;
					_near = _nearCast;
				}
			}
		}
	}


	if(p_direction.z < 0)
	{
		for(Uint16 x = 0; x <= ceil(p_dimension.x); x++)
		{
			for(Uint16 y = 0; y <= ceil(p_dimension.y); y++)
			{
				_nearCast = 0;
				_sideCast = 0;
				castRay(p_start + Vector3<GLfloat>(x * _dX + _c, y * _dY + _c, -_c), p_direction, _nearCast, _sideCast);
				if((_nearCast < _near) && (_sideCast & 4))
				{
					_side = 4;
					_near = _nearCast;
				}
			}
		}
	}
	if(p_direction.z > 0)
	{
		for(Uint16 x = 0; x <= ceil(p_dimension.x); x++)
		{
			for(Uint16 y = 0; y <= ceil(p_dimension.y); y++)
			{
				_nearCast = 0;
				_sideCast = 0;
				castRay(p_start + Vector3<GLfloat>(x * _dX + _c, y * _dY + _c, p_dimension.z + _c), p_direction, _nearCast, _sideCast);
				if((_nearCast < _near) && (_sideCast & 4))
				{
					_side = 4;
					_near = _nearCast;
				}
			}
		}
	}
	if(_side == 0)
		_near = 1;
	else
		_near = _near * 0.95f;
	p_near = _near;
	p_face = _side;
}
