#pragma once
#include "engine\utils\variable\datatype\Macros.h"
#include <fstream>

class FileExt
{
public:
	static void writeInt(std::ofstream& p_fileStream, Sint32 p_uint);
	static void writeShort(std::ofstream& p_fileStream, Sint16 p_ushort);
	static void writeChar(std::ofstream& p_fileStream, Uint8 p_uchar);
	static void writeString(std::ofstream& p_fileStream, std::string p_string);

	static Sint32 readInt(char* p_fileStream, Uint32& p_index);
	static Sint16 readShort(char* p_fileStream, Uint32& p_index);
	static Uint8 readChar(char* p_fileStream, Uint32& p_index);
	static std::string readString(char* p_fileStream, Uint32& p_index);
};
