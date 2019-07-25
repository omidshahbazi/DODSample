// DOD Sample
#pragma once
#include <Common\Vector2.h>

class OODAnt
{
public:
	OODAnt(Vector2F Position) :
		m_Position(Position)
	{
	}

	void Update(void)
	{
		m_Position.X++;
		m_Position.Y++;
	}

	const Vector2F &GetPosition(void) const
	{
		return m_Position;
	}

	const Vector2F &GetTarget(void) const
	{
		return m_Target;
	}

private:
	Vector2F m_Position;
	Vector2F m_Target;
};