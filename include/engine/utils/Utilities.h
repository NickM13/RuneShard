#pragma once

#pragma warning (disable : 4244)

#include "engine\utils\variable\datatype\Color.h"
#include "engine\utils\variable\datatype\Rectangle.h"
#include "engine\utils\variable\datatype\Vector2.h"
#include "engine\utils\variable\datatype\Vector3.h"
#include "engine\utils\variable\datatype\Vector4.h"
#include "engine\utils\variable\datatype\Macros.h"
#include "engine\utils\global\event\GKey.h"
#include "engine\utils\global\event\GMouse.h"
#include "engine\utils\global\GScreen.h"
#include "engine\utils\OpenGL.h"
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>

namespace Util {
	template<class T>
	static std::string numToString(T n, Uint16 p_decimalPlaces = 0) {
		try {
			return std::string(std::to_string(n)).substr(0, std::string(std::to_string(n)).find('.', 0) + p_decimalPlaces + (p_decimalPlaces > 0 ? 1 : 0));
		}
		catch(...) {
			std::cout << "Warning: Arg passed to Util::numToString( T n ) was not a number." << std::endl;;
		}
		return "0";
	}
	static std::string subchar(char* chararray, Uint32 start, Uint32 end) {
		std::string subbed;
		for(Uint32 i = start; i < end + 1; i++) {
			subbed += chararray[i];
		}
		return subbed;
	}
};
