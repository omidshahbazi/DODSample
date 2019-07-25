// DOD Sample
#pragma once

template<typename T>
struct Vector2
{
public:
	Vector2(void) :
		Vector2(0)
	{
	}

	Vector2(T Scalar) :
		Vector2(Scalar, Scalar)
	{
	}

	Vector2(T X, T Y) :
		X(X),
		Y(Y)
	{
	}

public:
	T X, Y;
};

typedef Vector2<float> Vector2F;