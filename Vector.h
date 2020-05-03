#pragma once


struct Vector2
{
	Vector2() : x(0), y(0) {};
	Vector2(float X, float Y) : x(X), y(Y) { };
	Vector2(float v) : x(v), y(v) {};
	float x, y;
};