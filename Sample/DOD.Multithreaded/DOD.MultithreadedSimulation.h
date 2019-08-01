// DOD Sample
#pragma once
#include <DOD\DODSimulation.h>

class DODMultithreadedSimulation : public DODSimulation
{
public:
	DODMultithreadedSimulation(Renderer *Renderer, int AntCount) :
		DODSimulation(Renderer, AntCount)
	{
	}

	virtual void Update(void) override;

	const char *GetName(void) override
	{
		return "DOD Multithreaded Simulation";
	}
};