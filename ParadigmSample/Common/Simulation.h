// DOD Sample
#pragma once
#include <Common\Vector2.h>

class Renderer;

class Simulation
{
public:
	Simulation(Renderer *Renderer, int AntCount) :
		m_Renderer(Renderer),
		m_AntCount(AntCount)
	{
	}

	virtual void Update(void) = 0;

	virtual void Render(void) = 0;

	virtual const char *GetName(void) = 0;

protected:
	Renderer * GetRenderer(void)
	{
		return m_Renderer;
	}

	int GetAntCount(void) const
	{
		return m_AntCount;
	}

private:
	Renderer * m_Renderer;
	int m_AntCount;
};