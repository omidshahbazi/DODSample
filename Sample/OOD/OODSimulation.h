// DOD Sample
#pragma once
#include <Application\Simulation.h>
#include <OOD\OODAnt.h>
#include <vector>

class OODSimulation : public Simulation
{
public:
	OODSimulation(Renderer *Renderer, int AntCount);

	void Update(void) override;

	const char *GetName(void) override
	{
		return "OOD Simulation";
	}

private:
	std::vector<OODAnt*> m_Ants;
};