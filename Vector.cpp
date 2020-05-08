#include "Vector.h"
#include "MathUtils.h"

std::istream& operator>>(std::istream& is, Vector2& vec)
{
	is >> vec.x >> vec.y;
	return is;
}

Vector2 Vector2::operator*(const Vector2& rhs) const
{
	return Vector2(x * rhs.x, y * rhs.y);
}

Vector2 Vector2::operator*(const float& rhs) const
{
	return Vector2(x * rhs, y * rhs);
}

Vector2& Vector2::operator*=(const Vector2& rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	return *this;
}

Vector2& Vector2::operator*=(const float& rhs)
{
	x *= rhs;
	y *= rhs;
	return *this;
}

Vector2 Vector2::operator/(const Vector2& rhs) const
{
	return Vector2(x / rhs.x, y / rhs.y);
}

Vector2 Vector2::operator/(const float& rhs) const
{
	return Vector2(x / rhs, y / rhs);
}

Vector2& Vector2::operator/=(const Vector2& rhs)
{
	x /= rhs.x;
	y /= rhs.y;
	return *this;
}

Vector2& Vector2::operator/=(const float& rhs)
{
	x /= rhs;
	y /= rhs;
	return *this;
}

Vector2 Vector2::operator+(const Vector2& rhs) const
{
	return Vector2(x + rhs.x, y + rhs.y);
}

Vector2& Vector2::operator+=(const Vector2& rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Vector2 Vector2::operator-(const Vector2& rhs) const
{
	return Vector2(x - rhs.x, y - rhs.y);
}

Vector2& Vector2::operator-=(const Vector2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

void Vector2::absoluteize()
{
	x = Util::Abs(x);
	y = Util::Abs(y);
}

Vector2 Vector2::absolute() const
{
	return Vector2(Util::Abs(x), Util::Abs(y));
}

void Vector2::normalize()
{
	if (x == 0 && y == 0)
	{ //normalized zero vector is just zero vector
		return;
	}
	*this /= distance(0);
}

Vector2 Vector2::normalized() const
{
	Vector2 newVec(*this);
	newVec.normalize();
	return newVec;
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
	return (a.x - b.x) * (a.x - b.x) +
		(a.y - b.y) * (a.y - b.y);
}
float Vector2::distance(Vector2 a, Vector2 b)
{
	return sqrtf(Vector2::sqDistance(a, b));
}

Vector2 Vector2::normalized(const Vector2& vec)
{
	return vec.normalized();
}