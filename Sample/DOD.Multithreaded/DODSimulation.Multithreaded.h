// DOD Sample
#pragma once
#include <DOD\DODSimulation.h>

class DODSimulationMultithreaded : public DODSimulation
{
public:
	DODSimulationMultithreaded(Renderer *Renderer, int AntCount) :
		DODSimulation(Renderer, AntCount)
	{
	}

	virtual void Update(void) override;

	const char *GetName(void) override
	{
		return "DOD Multithreaded Simulation";
	}
};