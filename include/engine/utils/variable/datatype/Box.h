#pragma once
#include "engine\utils\LOpenGL.h"
#include "engine\utils\variable\datatype\Vector3.h"

// 3d box
struct Box {
private:
	Vector3<double> m_position;		// Position after rotating
	Vector3<double> m_offset;		// Position before rotating
	Vector3<double> m_size;
	Vector3<double> m_rotation;
public:
	Box(Vector3<double> p_position, Vector3<double> p_offset, Vector3<double> p_size, Vector3<double> p_rotation) 
		: m_position(p_position), m_offset(p_offset), m_size(p_size), m_rotation(p_rotation) { }

	bool isInside(Box &p_box) {

	}

	void render() {
		
	}
};
