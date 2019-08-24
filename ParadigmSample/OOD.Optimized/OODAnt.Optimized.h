// DOD Sample
#pragma once
#include <Common\Vector2.h>

class Renderer;

class OODAntOptimized
{
public:
	OODAntOptimized(Vector2F Position) :
		m_Position(Position),
		m_StepCount(0)
	{
		FindNewTarget();
	}

	void Update(void);

	void Render(Renderer &Renderer);

	const Vector2F &GetPosition(void) const
	{
		return m_Position;
	}

private:
	void FindNewTarget(void);

private:
	Vector2F m_Position;
	Vector2F m_Step;
	int m_StepCount;
};