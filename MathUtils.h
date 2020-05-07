#pragma once

#include "Vector.h"
#include <math.h>

namespace Util
{
	template<typename T>
	T Clamp(const T& value, const T& min, const T& max)
	{
		return value > max ? max : value < min ? min : value;
	}

	template<typename T>
	void ClampInPlace(T& value, const T& min, const T& max)
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
}

