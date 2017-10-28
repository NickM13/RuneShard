#pragma once
#include "engine\utils\variable\datatype\Vector3.h"
#include "engine\utils\variable\datatype\Macros.h"
#include <random>

class Perlin {
private:
	static float perlin(float x, float y, float z);

	static const Uint8 m_permutation[256];
	static Uint8* p;
public:
	static void initPerlin(Uint32 p_seed);
	static float perlinNoise(float x, float y, float z, Sint16 p_octaves, float p_persistence);

};
