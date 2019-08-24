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

	float GetSquaredMagnitude(void) const
	{
		return (X * X) + (Y * Y);
	}

	float GetMagnitude(void) const
	{
		return sqrtf(GetSquaredMagnitude());
	}

	Vector2 GetNormalized(void) const
	{
		float mag = GetMagnitude();

		return Vector2(X / mag, Y / mag);
	}

	bool operator == (const Vector2 &Other) const
	{
		return (Other.X == X && Other.Y == Y);
	}

	bool operator != (const Vector2 &Other) const
	{
		return !(*this == Other);
	}

	Vector2 &operator += (const Vector2 &Other)
	{
		X += Other.X;
		Y += Other.Y;
		return *this;
	}

	Vector2 operator - (const Vector2 &Other) const
	{
		return Vector2(X - Other.X, Y - Other.Y);
	}

	Vector2 operator * (float Scalar) const
	{
		return Vector2(X * Scalar, Y * Scalar);
	}

	Vector2 operator * (const Vector2 &Other) const
	{
		return Vector2(X * Other.X, Y * Other.Y);
	}

	Vector2 operator / (float Scalar) const
	{
		return Vector2(X / Scalar, Y / Scalar);
	}

	Vector2 operator / (const Vector2 &Other) const
	{
		return Vector2(X / Other.X, Y / Other.Y);
	}

public:
	T X, Y;
};

typedef Vector2<float> Vector2F;