#pragma once

#include "Macros.h"

struct Voxel
{
	Sint8 interactionType;
	Uint16 color;

	Voxel() {};
	Voxel(Sint8 p_interaction, Uint16 p_color) : interactionType(p_interaction), color(p_color) {};

	bool operator==(Voxel p_vox)
	{
		return (interactionType == p_vox.interactionType &&
				color == p_vox.color);
	}
};
