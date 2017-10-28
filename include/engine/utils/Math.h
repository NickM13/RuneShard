#pragma once
#include "engine\utils\variable\datatype\Macros.h"
#include "engine\utils\variable\datatype\Vector2.h"
#include "engine\utils\variable\datatype\Vector3.h"

class Math
{
private:
	static double TINY_OFFSET;
	static Vector3<double> TINY_BOX_OFFSET;
public:
	static double round2f(double p_f, Sint32 p_decimalPlaces);
	// sin of decimal number
	static double sind(double p_f);
	// cos of decimal number
	static double cosd(double p_f);
	// tan of decimal number
	static double tand(double p_f);
	// Does not use z-axis rotation
	static Vector3<double> computeDirection(Vector3<double> p_rotation);

	static Vector3<double> flipOverPoint(Vector3<double> p_start, Vector3<double> p_len, Vector3<double> p_point, bool p_flip[3]);
	static void castRay3d(Vector3<double> p_start, Vector3<double> p_direction, Vector3<double> p_boxPosition, Vector3<double> p_boxDimension, double &p_near, double &p_far, Sint8 &p_side);
	static void castBox3d(Vector3<double> p_start, Vector3<double> p_dimension, Vector3<double> p_direction, Vector3<double> p_boxPosition, Vector3<double> p_boxDimension, double &p_near, double &p_far, Sint8 &p_side);
	static double smoothChange(double x1, double x2, double p_rateOfChange, double p_time);
	static Vector2<double> smoothChangeVec2(Vector2<double> x1, Vector2<double> x2, double p_rateOfChange, double p_time);
	static Vector3<double> smoothChangeVec3(Vector3<double> x1, Vector3<double> x2, double p_rateOfChange, double p_time);
};
