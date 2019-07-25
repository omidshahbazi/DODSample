// DOD Sample
#pragma once
#include <Common\Vector2.h>
#include <random>

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

	virtual const char *GetName(void) = 0;

	static float GetRandom(float Min, float Max)
	{
		return Min + (rand() % (int)(Max - Min));
	}

	static Vector2F GetRandom(float MinX, float MaxX, float MinY, float MaxY)
	{
		return { GetRandom(MinX, MaxX), GetRandom(MinY, MaxY) };
	}

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