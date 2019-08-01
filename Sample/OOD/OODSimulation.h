// DOD Sample
#pragma once
#include <Common\Simulation.h>
#include <OOD\OODAnt.h>
#include <vector>

class OODSimulation : public Simulation
{
public:
	OODSimulation(Renderer *Renderer, int AntCount);

	virtual void Update(void) override;

	virtual void Render(void) override;

	const char *GetName(void) override
	{
		return "OOD Simulation";
	}

protected:
	std::vector<OODAnt*> m_Ants;
};