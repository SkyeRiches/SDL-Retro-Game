#ifndef _MATHUTILITY_H_
#define _MATHUTILITY_H_

#include <math.h>

#define PI 3.14159265
#define DEG_TO_RAD PI / 180.0f

// Structure for creating and using vector2
struct Vector2
{
	float x;
	float y;

	Vector2(float a_x = 0.0f, float a_y = 0.0f) : x(a_x), y(a_y) {}

	float MagnitudeSqrd()
	{
		return x * x + y * y;
	}

	float Magnitude()
	{
		return (float)sqrt(MagnitudeSqrd());
	}

	Vector2 Normalised()
	{
		float fMagnitude = Magnitude();
		return Vector2(x / fMagnitude, y / fMagnitude);
	}
};

// Overload operator for adding 2 vectors together
inline Vector2 operator +(const Vector2& a_vLeftSide, const Vector2& a_vRightSide)
{
	return Vector2(a_vLeftSide.x + a_vRightSide.x, a_vLeftSide.y + a_vRightSide.y);
}

// Overload operator for subtracting 2 vectors together
inline Vector2 operator -(const Vector2& a_vLeftSide, const Vector2& a_vRightSide)
{
	return Vector2(a_vLeftSide.x - a_vRightSide.x, a_vLeftSide.y - a_vRightSide.y);
}

// Overload operator for multiplying 2 vectors
inline Vector2 operator *(const Vector2& a_vLeftSide, const Vector2& a_vRightSide)
{
	return Vector2(a_vLeftSide.x * a_vRightSide.x, a_vLeftSide.y * a_vRightSide.y);
}

// Overload operator for dividing 2 vectors
inline Vector2 operator /(const Vector2& a_vLeftSide, const Vector2& a_vRightSide)
{
	return Vector2(a_vLeftSide.x / a_vRightSide.x, a_vLeftSide.y / a_vRightSide.y);
}

// Function to rotate a vector by a specified angle
inline Vector2 RotateVector(Vector2& a_vVector, float a_fAngle)
{
	float fRadAngle = (float)(a_fAngle * DEG_TO_RAD);
	return Vector2(
		(float)a_vVector.x * cos(fRadAngle) - a_vVector.y * sin(fRadAngle),
		(float)a_vVector.x * sin(fRadAngle) + a_vVector.y * cos(a_fAngle));
}

#endif // !_MATHUTILITY_H_

