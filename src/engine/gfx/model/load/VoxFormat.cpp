#include "engine\gfx\model\load\VoxFormat.h"
#include "engine\utils\FileExt.h"

struct Chunk_t
{
	Uint32 id;
	Uint32 contentSize;
	Uint32 childrenSize;
};

Sint32 MV_ID(Sint32 a, Sint32 b, Sint32 c, Sint32 d) {
	return (a) | (b << 8) | (c << 16) | (d << 24);
}

void readChunk(char* p_data, Uint32& p_index, Chunk_t &chunk) {
	chunk.id = FileExt::readInt(p_data, p_index);
	chunk.contentSize = FileExt::readInt(p_data, p_index);
	chunk.childrenSize = FileExt::readInt(p_data, p_index);
}
void VoxFormat::loadModel(std::string p_filename, std::vector<VoxelMatrix>& p_matrixList)
{
	std::ifstream _file;

	Uint32 _length, _index;
	char* _data;

	Uint32 numVoxels;

	const Sint32 MV_VERSION = 150;

	const Uint32 ID_VOX = MV_ID('V', 'O', 'X', ' ');
	const Uint32 ID_MAIN = MV_ID('M', 'A', 'I', 'N');
	const Uint32 ID_SIZE = MV_ID('S', 'I', 'Z', 'E');
	const Uint32 ID_XYZI = MV_ID('X', 'Y', 'Z', 'I');
	const Uint32 ID_RGBA = MV_ID('R', 'G', 'B', 'A');
	const Uint32 ID_MATT = MV_ID('M', 'A', 'T', 'T');
	const Uint32 ID_PACK = MV_ID('P', 'A', 'C', 'K');

	_file.open(std::string("res\\model\\" + p_filename + ".vox").c_str(), std::ios::binary);
	{
		if(!_file.good())
		{
			std::cout << "Error: File \"res\\model\\" << p_filename << ".vox\" not found." << std::endl;
			goto end;
		}

		_index = 0;

		_file.seekg(0, _file.end);
		_length = Uint32(_file.tellg());
		_file.seekg(0, _file.beg);
		_data = new char[_length];
		_file.read(_data, _length);

		Uint32 magic = FileExt::readInt(_data, _index);
		if(magic != ID_VOX)
		{
			std::cout << "Magic number does not match" << std::endl;
			goto end;
		}

		Uint32 version = FileExt::readInt(_data, _index);
		if(version != MV_VERSION)
		{
			std::cout << "Version does not match" << std::endl;
			goto end;
		}

		Chunk_t mainChunk;
		readChunk(_data, _index, mainChunk);
		if(mainChunk.id != ID_MAIN)
		{
			std::cout << "Main chunk is not found" << std::endl;
			goto end;
		}

		_index += mainChunk.contentSize;


		while(_index < _length)
		{
			Chunk_t sub;
			readChunk(_data, _index, sub);

			if(sub.id == ID_SIZE)
			{
				p_matrixList.clear();
				Vector3<Sint32> size;
				size.x = FileExt::readInt(_data, _index);
				size.z = FileExt::readInt(_data, _index);
				size.y = FileExt::readInt(_data, _index);
				p_matrixList.push_back(VoxelMatrix("Vox", {}, size));
			}
			else if(sub.id == ID_XYZI)
			{
				numVoxels = FileExt::readInt(_data, _index);
				struct Vox
				{
					Uint8 x, y, z, i;
				} vox;
				for(Uint16 i = 0; i < numVoxels; i++)
				{
					vox.x = p_matrixList[0].getSize().x - FileExt::readChar(_data, _index) - 1;
					vox.z = p_matrixList[0].getSize().z - FileExt::readChar(_data, _index) - 1;
					vox.y = FileExt::readChar(_data, _index);
					vox.i = FileExt::readChar(_data, _index);
					//p_matrixList[0].setVoxel(Vector3<Sint32>(vox.x, vox.y, vox.z), Voxel(1, MColor::getUnitID(Color((m_palette[vox.i] & 0x00FF0000) / 256, m_palette[vox.i] & 0x0000FF00, m_palette[vox.i] & 0x000000FF))));
				}
			}
			else if(sub.id == ID_PACK)
			{
				_index += sub.contentSize;
			}
			else if(sub.id == ID_RGBA)
			{
				for(Uint16 i = 0; i < 255; i++)
				{
					Uint32 color = FileExt::readInt(_data, _index);
					setPalette(i + 1, color);
				}
			}
			/*
			else if(sub.id == ID_MATT)
			{

			}
			*/
		}

		delete[] _data;
	}
end:
	_file.close();
}
