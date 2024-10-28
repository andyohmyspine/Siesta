#pragma once

#include "SiestaTypes.h"

template<CReal T>
struct PVector2D
{
	T X;
	T Y;

	PVector2D() : X(T()), Y(T()) {}
	PVector2D(T Scalar) : X(Scalar), Y(Scalar) {}
	PVector2D(T InX, T InY) : X(InX), Y(InY) {}

	PVector2D(const PVector2D& Other) : X(Other.X), Y(Other.Y) {}
	PVector2D& operator=(const PVector2D& Other)
	{
		X = Other.X;
		Y = Other.Y;
		return *this;
	}
};