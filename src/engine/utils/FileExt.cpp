#include "engine\utils\FileExt.h"

void FileExt::writeInt(std::ofstream& p_fileStream, Sint32 p_uint) {
	p_fileStream << Uint8((p_uint & 0xFF));
	p_fileStream << Uint8((p_uint & 0xFF00) >> 8);
	p_fileStream << Uint8((p_uint & 0xFF0000) >> 16);
	p_fileStream << Uint8((p_uint & 0xFF000000) >> 24);
}
void FileExt::writeShort(std::ofstream& p_fileStream, Sint16 p_ushort) {
	p_fileStream << Uint8((p_ushort & 0xFF));
	p_fileStream << Uint8((p_ushort & 0xFF00) >> 8);
}
void FileExt::writeChar(std::ofstream& p_fileStream, Uint8 p_uchar) {
	p_fileStream << p_uchar;
}
void FileExt::writeString(std::ofstream& p_fileStream, std::string p_string) {
	writeChar(p_fileStream, (Uint8)p_string.length());
	for(Uint16 i = 0; i < p_string.length(); i++)
		p_fileStream << p_string[i];
}

Sint32 FileExt::readInt(char* p_fileStream, Uint32& p_index) {
	Sint32 _value = 0;
	_value += readChar(p_fileStream, p_index);
	_value += readChar(p_fileStream, p_index) << 8;
	_value += readChar(p_fileStream, p_index) << 16;
	_value += readChar(p_fileStream, p_index) << 24;
	return _value;
}
Sint16 FileExt::readShort(char* p_fileStream, Uint32& p_index) {
	Sint16 _value = 0;
	_value += readChar(p_fileStream, p_index);
	_value += readChar(p_fileStream, p_index) << 8;
	return _value;
}
Uint8 FileExt::readChar(char* p_fileStream, Uint32& p_index) {
	p_index = p_index + 1;
	return Uint8(p_fileStream[p_index - 1]);
}
std::string FileExt::readString(char* p_fileStream, Uint32& p_index) {
	std::string str = "";
	Uint8 size = readChar(p_fileStream, p_index);
	for(Uint8 i = 0; i < size; i++)
		str += ((char)readChar(p_fileStream, p_index));
	return str;
}
