#pragma once

#include "Vector.h"
#include <math.h>

namespace Util
{
	template<typename T>
	T Clamp(T value, T min, T max)
	{
		return value > max ? max : value < min ? min : value;
	}

	template<typename T>
	void ClampInPlace(T& value, T min, T max)
	{
		if (value < min)
		{
			value = min;
		}
		else if (value > max)
		{
			value = max;
		}
	}

	float SqDistance(Vector2 a, Vector2 b)
	{
		return (a.x * b.x) + (a.y * b.y);
	}

	float Distance(Vector2 a, Vector2 b)
	{
		return sqrtf(SqDistance(a, b));
	}
}

