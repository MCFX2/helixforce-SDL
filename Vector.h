#pragma once

#include <iostream>

struct Vector2
{
	Vector2() : x(0), y(0) {};
	Vector2(float X, float Y) : x(X), y(Y) { };
	Vector2(float v) : x(v), y(v) {};
	float x, y;

	friend std::istream& operator>>(std::istream&, Vector2&);

	float distance(Vector2);
	float sqDistance(Vector2);

	static float distance(Vector2, Vector2);
	static float sqDistance(Vector2, Vector2);
};

