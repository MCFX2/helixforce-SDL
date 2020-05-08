#pragma once

#include <iostream>

struct Vector2
{
	Vector2() : x(0), y(0) {};
	Vector2(float X, float Y) : x(X), y(Y) { };
	Vector2(float v) : x(v), y(v) {};
	float x, y;

	friend std::istream& operator>>(std::istream&, Vector2&);

	Vector2 operator*(const Vector2&) const;
	Vector2 operator*(const float&) const;
	Vector2& operator*=(const Vector2&);
	Vector2& operator*=(const float&);
	Vector2 operator/(const Vector2&) const;
	Vector2 operator/(const float&) const;
	Vector2& operator/=(const Vector2&);
	Vector2& operator/=(const float&);
	Vector2 operator+(const Vector2&) const;
	Vector2& operator+=(const Vector2&);
	Vector2 operator-(const Vector2&) const;
	Vector2& operator-=(const Vector2&);

	void absoluteize(); //transforms a vector to be absolute

	Vector2 absolute() const;

	//gets the distance between two Vec2s, prefer sqDistance() when possible as it is faster.
	float distance(Vector2);
	//gets the distance between two Vec2s, squared.
	float sqDistance(Vector2);

	//modifies the vector to have a magnitude of 1, but the same direction.
	void normalize();
	//returns a new vector, normalized of the input vector.
	Vector2 normalized() const;

	//nonmember versions of some useful functions
	static float distance(Vector2, Vector2);
	static float sqDistance(Vector2, Vector2);

	static Vector2 normalized(const Vector2&);
};

