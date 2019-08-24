// DOD Sample
#pragma once
#include <Common\Simulation.h>
#include <OOD.Optimized\OODAnt.Optimized.h>
#include <vector>

class OODSimulationOptimized : public Simulation
{
public:
	OODSimulationOptimized(Renderer *Renderer, int AntCount);

	virtual void Update(void) override;

	virtual void Render(void) override;

	const char *GetName(void) override
	{
		return "OOD Optimized Simulation";
	}

protected:
	OODAntOptimized* m_Ants;
};