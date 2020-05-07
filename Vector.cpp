#include "Vector.h"

std::istream& operator>>(std::istream& is, Vector2& vec)
{
	is >> vec.x >> vec.y;
	return is;
}

float Vector2::sqDistance(Vector2 b)
{
	return Vector2::sqDistance(*this, b);
}

float Vector2::distance(Vector2 b)
{
	return Vector2::distance(*this, b);
}

float Vector2::sqDistance(Vector2 a, Vector2 b)
{
	return (a.x * b.x) + (a.y * b.y);
}
float Vector2::distance(Vector2 a, Vector2 b)
{
	return sqrtf(Vector2::sqDistance(a, b));
}