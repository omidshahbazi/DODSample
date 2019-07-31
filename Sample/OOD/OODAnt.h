// DOD Sample
#pragma once
#include <Common\Vector2.h>

class Renderer;

class OODAnt
{
public:
	OODAnt(Vector2F Position) :
		m_Position(Position),
		m_StepCount(0)
	{
		FindNewTarget();
	}

	void Update(void);

	void Render(Renderer *Renderer);

	void FindNewTarget(void);

	const Vector2F &GetPosition(void) const
	{
		return m_Position;
	}

	const Vector2F &GetStep(void) const
	{
		return m_Step;
	}

private:
	Vector2F m_Position;
	Vector2F m_Step;
	int m_StepCount;
};