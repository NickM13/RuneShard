#include "engine\gfx\model\load\NvmFormat.h"
#include "engine\utils\FileExt.h"

void NvmFormat::loadModel(std::string p_fileName, std::vector<VoxelMatrix*> &p_matrixList) {
	std::ifstream _file;
	Uint32 _length, _index;
	char* _data;
	_file.open(std::string(p_fileName).c_str(), std::ios::binary);
	{
		if(!_file.good()) {
			std::cerr << "Error: File \"" << p_fileName << "\" not found." << std::endl;
			_file.close();
			return;
		}
		_index = 0;
		_file.seekg(0, _file.end);
		_length = Uint32(_file.tellg());
		_file.seekg(0, _file.beg);
		_data = new char[_length];
		_file.read(_data, _length);

		Sint32 nvm, version, blank, matrixCount;
		VoxelMatrix* m;
		std::string name;
		Vector3<Sint16> pos, size;
		Sint32 volume;
		Sint32 matrixIndex;
		Uint8 count, r, g, b, a;
		Voxel vox;
		nvm = FileExt::readInt(_data, _index); // Skip ".NVM"
		version = FileExt::readInt(_data, _index);
		blank = FileExt::readInt(_data, _index);
		matrixCount = FileExt::readInt(_data, _index);
		for(Uint16 i = 0; i < matrixCount; i++) {
			// Matrix Header
			name = FileExt::readString(_data, _index);
			pos.x = FileExt::readShort(_data, _index);
			pos.y = FileExt::readShort(_data, _index);
			pos.z = FileExt::readShort(_data, _index);
			size.x = FileExt::readShort(_data, _index);
			size.y = FileExt::readShort(_data, _index);
			size.z = FileExt::readShort(_data, _index);
			m = new VoxelMatrix(name, Vector3<GLfloat>(pos) / 2, size);
			volume = size.x * size.y * size.z;
			matrixIndex = 0;
			while(matrixIndex < volume) {
				count = FileExt::readChar(_data, _index);
				r = FileExt::readChar(_data, _index);
				g = FileExt::readChar(_data, _index);
				b = FileExt::readChar(_data, _index);
				a = FileExt::readChar(_data, _index);
				vox = Voxel(a, MColor::getColorId(Color(r / 255.f, g / 255.f, b / 255.f)));
				for(Sint32 i = matrixIndex; i < matrixIndex + count; i++)
					m->setVoxel(Vector3<Sint32>(fmod(floorf(GLfloat(i) / (size.z * size.y)), size.x), fmod(floorf(GLfloat(i) / (size.z)), size.y), fmod(i, size.z)), vox);
				matrixIndex += count;
			}
			p_matrixList.push_back(m);
		}
		delete[] _data;
	}
	_file.close();
}
