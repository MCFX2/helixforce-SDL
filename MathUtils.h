#pragma once

#include "Vector.h"
#include <math.h>

namespace Util
{
	//Returns a value clamped between two other values.
	//Type must have '<(T)' and '>(T)' operators.
	template<typename T>
	inline T Clamp(const T& value, const T& min, const T& max) {
		return value > max ? max : value < min ? min : value;
	}

	//Clamps a value in-place by reference.
	//Type must have functional '<(T)', '>(T)', and '=(T)' operators.
	template<typename T>
	inline void ClampInPlace(T& value, const T& min, const T& max) {
		if (value < min) {
			value = min;
		}
		else if (value > max) {
			value = max;
		}
	}

	//Returns the absolute value of a value.
	//Type must have '<(integral)' operator and unary '-' operator.
	template<typename T>
	inline T Abs(const T& value) {
		if (value < 0) return -value;
		return value;
	}

	template<>
	inline Vector2 Abs(const Vector2& value) {
		return value.absolute();
	}
}

