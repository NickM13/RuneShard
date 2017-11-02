#include "engine\utils\Math.h"
#include "engine\utils\variable\datatype\Voxel.h"

double Math::TINY_OFFSET = 0.00001;
Vector3<double> Math::TINY_BOX_OFFSET = Vector3<double>(0.001, 0.001, 0.001);

double Math::round2f(double p_f, Sint32 p_decimalPlaces) {
	return double(round(p_f * double(pow(10, p_decimalPlaces))) / pow(10, p_decimalPlaces));
}
// sin of decimal number
double Math::sind(double p_f) {
	return double(sin((double)(p_f * 3.14159265359 / 180)));
}
// cos of decimal number
double Math::cosd(double p_f) {
	return double(cos((double)(p_f * 3.14159265359 / 180)));
}
// tan of decimal number
double Math::tand(double p_f) {
	return double(tan((double)(p_f * 3.14159265359 / 180)));
}
// Does not use z-axis rotation
Vector3<double> Math::computeDirection(Vector3<double> p_rotation) {
	double ydist = double(2 * sind(p_rotation.x));
	double xdist = double(sqrt(pow(2, 2) - pow(ydist, 2)));
	double zdist = double(xdist * sind(p_rotation.y));
	xdist = xdist * sind((p_rotation.y - 90));
	return Vector3< double >(zdist, -ydist, xdist).getNormal();
}

Vector3<double> Math::flipOverPoint(Vector3<double> p_start, Vector3<double> p_len, Vector3<double> p_point, bool p_flip[3]) {
	if(p_flip[0]) p_start.x = (p_start.x - (p_start.x - p_point.x) * 2) - p_len.x;
	if(p_flip[1]) p_start.y = (p_start.y - (p_start.y - p_point.y) * 2) - p_len.y;
	if(p_flip[2]) p_start.z = (p_start.z - (p_start.z - p_point.z) * 2) - p_len.z;
	return p_start;
}

void Math::castRay3d(Vector3<double> p_start, Vector3<double> p_direction, Vector3<double> p_boxPosition, Vector3<double> p_boxDimension, double &p_near, double &p_far, Sint8 &p_side) {
	p_boxPosition = p_boxPosition - TINY_BOX_OFFSET;
	p_boxDimension = p_boxDimension + TINY_BOX_OFFSET * 2;
	double _near = p_near, _far = p_far;
	p_near = 0;
	Sint8 _side = 0;
	bool flip[3] = {p_direction.x < 0, p_direction.y < 0, p_direction.z < 0};
	p_boxPosition = flipOverPoint(p_boxPosition, p_boxDimension, p_start, flip);
	if(p_direction.x < 0)
		p_direction.x = -p_direction.x;
	if(p_direction.y < 0)
		p_direction.y = -p_direction.y;
	if(p_direction.z < 0)
		p_direction.z = -p_direction.z;
	if(p_direction.x != 0) {
		if(p_start.x > p_boxPosition.x + p_boxDimension.x) {
			_near = 1;
			_far = 0;
		}
		else {
			_near = fmax(_near, (p_boxPosition.x - p_start.x) / (p_direction.x));
			_far = fmin(_far, (p_boxPosition.x + p_boxDimension.x - p_start.x) / (p_direction.x));
			if(_near > p_near) {
				_side = flip[0] ? FACE_NORTH : FACE_SOUTH;
				p_near = _near;
			}
		}
	}
	else if(p_start.x < p_boxPosition.x || p_start.x > p_boxPosition.x + p_boxDimension.x) {
		_near = 1;
		_far = 0;
	}
	else {
		_near = fmax(_near, 0);
		_far = fmin(_far, 1);
		if(_near > p_near) {
			_side = flip[0] ? FACE_NORTH : FACE_SOUTH;
			p_near = _near;
		}
	}
	if(p_direction.y != 0) {
		if(p_start.y > p_boxPosition.y + p_boxDimension.y) {
			_near = 1;
			_far = 0;
		}
		else {
			_near = fmax(_near, (p_boxPosition.y - p_start.y) / (p_direction.y));
			_far = fmin(_far, (p_boxPosition.y + p_boxDimension.y - p_start.y) / (p_direction.y));
			if(_near > p_near) {
				_side = flip[1] ? FACE_TOP : FACE_BOTTOM;
				p_near = _near;
			}
		}
	}
	else if(p_start.y < p_boxPosition.y || p_start.y > p_boxPosition.y + p_boxDimension.y) {
		_near = 1;
		_far = 0;
	}
	else {
		_near = fmax(_near, 0);
		_far = fmin(_far, 1);
		if(_near > p_near) {
			_side = flip[1] ? FACE_TOP : FACE_BOTTOM;
			p_near = _near;
		}
	}
	if(p_direction.z != 0) {
		if(p_start.z > p_boxPosition.z + p_boxDimension.z) {
			_near = 1;
			_far = 0;
		}
		else {
			_near = fmax(_near, (p_boxPosition.z - p_start.z) / (p_direction.z));
			_far = fmin(_far, (p_boxPosition.z + p_boxDimension.z - p_start.z) / (p_direction.z));
			if(_near > p_near) {
				_side = flip[2] ? FACE_EAST : FACE_WEST;
				p_near = _near;
			}
		}
	}
	else if(p_start.z < p_boxPosition.z || p_start.z > p_boxPosition.z + p_boxDimension.z) {
		_near = 1;
		_far = 0;
	}
	else {
		_near = fmax(_near, 0);
		_far = fmin(_far, 1);
		if(_near > p_near) {
			_side = flip[2] ? FACE_EAST : FACE_WEST;
			p_near = _near;
		}
	}

	if(_near < _far) {
		p_side = _side;
		p_far = _far + TINY_OFFSET;
	}
	else {
		p_side = 0;
		p_near = 1;
		p_far = 0;
	}
}

void Math::castBox3d(Vector3<double> p_start, Vector3<double> p_dimension, Vector3<double> p_direction, Vector3<double> p_boxPosition, Vector3<double> p_boxDimension, double &p_near, double &p_far, Sint8 &p_side) {
	double _near = 1, _nearCast;
	double _far = 1;
	Sint8 _side = 0, _sideCast;
	double _c = 0.0001; // Slight offset for corners to cast from
	Vector3<double> _dCount = (p_dimension / (p_boxDimension)).ceil();
	Vector3<double> _dOffset = p_dimension / (_dCount)-_c * 2;
	p_direction = p_direction.getNormal();
	if(p_direction.x < 0) {
		for(Uint16 y = 0; y <= _dCount.y; y++) {
			for(Uint16 z = 0; z <= _dCount.z; z++) {
				_nearCast = 0;
				_sideCast = 0;
				_far = 1;
				castRay3d(p_start + Vector3<double>(-_c, y * _dOffset.y + _c, z * _dOffset.z + _c), p_direction, p_boxPosition, p_boxDimension, _nearCast, _far, _sideCast);
				if((_nearCast < _near) && ((_sideCast & FACE_NORTH) || _nearCast < _c)) {
					_side = 1;
					_near = _nearCast;
				}
			}
		}
	}
	else {
		for(Uint16 y = 0; y <= _dCount.y; y++) {
			for(Uint16 z = 0; z <= _dCount.z; z++) {
				_nearCast = 0;
				_sideCast = 0;
				_far = 1;
				castRay3d(p_start + Vector3<double>(p_dimension.x + _c, y * _dOffset.y + _c, z * _dOffset.z + _c), p_direction, p_boxPosition, p_boxDimension, _nearCast, _far, _sideCast);
				if((_nearCast < _near) && ((_sideCast & FACE_SOUTH) || _nearCast < _c)) {
					_side = 1;
					_near = _nearCast;
				}
			}
		}
	}
	if(p_direction.y < 0) {
		for(Uint16 x = 0; x <= _dCount.x; x++) {
			for(Uint16 z = 0; z <= _dCount.z; z++) {
				_nearCast = 0;
				_sideCast = 0;
				_far = 1;
				castRay3d(p_start + Vector3<double>(x * _dOffset.x + _c, -_c, z * _dOffset.z + _c), p_direction, p_boxPosition, p_boxDimension, _nearCast, _far, _sideCast);
				if((_nearCast < _near) && ((_sideCast & FACE_TOP) || _nearCast < _c)) {
					_side = 2;
					_near = _nearCast;
				}
			}
		}
	}
	else {
		for(Uint16 x = 0; x <= _dCount.x; x++) {
			for(Uint16 z = 0; z <= _dCount.z; z++) {
				_nearCast = 0;
				_sideCast = 0;
				_far = 1;
				castRay3d(p_start + Vector3<double>(x * _dOffset.x + _c, p_dimension.y + _c, z * _dOffset.z + _c), p_direction, p_boxPosition, p_boxDimension, _nearCast, _far, _sideCast);
				if((_nearCast < _near) && ((_sideCast & FACE_BOTTOM) || _nearCast < _c)) {
					_side = 2;
					_near = _nearCast;
				}
			}
		}
	}
	if(p_direction.z < 0) {
		for(Uint16 x = 0; x <= _dCount.x; x++) {
			for(Uint16 y = 0; y <= _dCount.y; y++) {
				_nearCast = 0;
				_sideCast = 0;
				_far = 1;
				castRay3d(p_start + Vector3<double>(x * _dOffset.x + _c, y * _dOffset.y + _c, -_c), p_direction, p_boxPosition, p_boxDimension, _nearCast, _far, _sideCast);
				if((_nearCast < _near) && ((_sideCast & FACE_EAST) || _nearCast < _c)) {
					_side = 4;
					_near = _nearCast;
				}
			}
		}
	}
	else {
		for(Uint16 x = 0; x <= _dCount.x; x++) {
			for(Uint16 y = 0; y <= _dCount.y; y++) {
				_nearCast = 0;
				_sideCast = 0;
				_far = 1;
				castRay3d(p_start + Vector3<double>(x * _dOffset.x + _c, y * _dOffset.y + _c, p_dimension.z + _c), p_direction, p_boxPosition, p_boxDimension, _nearCast, _far, _sideCast);
				if((_nearCast < _near) && ((_sideCast & FACE_WEST) || _nearCast < _c)) {
					_side = 4;
					_near = _nearCast;
				}
			}
		}
	}
	if(_side == 0) {
		for(Uint16 x = 0; x <= _dCount.x; x++) {
			for(Uint16 y = 0; y <= _dCount.y; y++) {
				for(Uint16 z = 0; z <= _dCount.z; z++) {
					_nearCast = 0;
					_sideCast = 0;
					_far = 1;
					castRay3d(p_start + Vector3<double>(x * _dOffset.x + _c, y * _dOffset.y + _c, z * _dOffset.z + _c), p_direction, p_boxPosition, p_boxDimension, _nearCast, _far, _sideCast);
					if((_nearCast < _near) && (_sideCast & 4)) {
						_side = 4 + 2 + 1;
						_near = _nearCast;
					}
				}
			}
		}
	}
	if(_side == 0)
		_near = 1;
	else
		_near = _near * 0.95f;
	p_near = _near;
	p_side = _side;
}
#include <iostream>
double Math::smoothChange(double x1, double x2, double p_rateOfChange, double p_time) {
	double diff = x2 - x1;
	double diffa = fabs(diff);
	double change = 0;
	if(diffa > 0.001) {
		change = p_rateOfChange * (pow(diffa, 2) - pow(fmax(0, diffa - p_time), 2));
		change = fmax(0, fmin(change, diffa));
		if(diff < 0)
			change = -change;
	}
	else
		change = diff;
	return change;
}

Vector2<double> Math::smoothChangeVec2(Vector2<double> x1, Vector2<double> x2, double p_rateOfChange, double p_time) {
	Vector2<double> change = {};
	change.x = smoothChange(x1.x, x2.x, p_rateOfChange, p_time);
	change.y = smoothChange(x1.y, x2.y, p_rateOfChange, p_time);
	return change;
}

Vector3<double> Math::smoothChangeVec3(Vector3<double> x1, Vector3<double> x2, double p_rateOfChange, double p_time) {
	Vector3<double> change = {};
	change.x = smoothChange(x1.x, x2.x, p_rateOfChange, p_time);
	change.y = smoothChange(x1.y, x2.y, p_rateOfChange, p_time);
	change.z = smoothChange(x1.z, x2.z, p_rateOfChange, p_time);
	return change;
}
