// DOD Sample
#pragma once
#include <Application\Simulation.h>
#include <DOD\DODAnt.h>
#include <vector>

class DODSimulation : public Simulation
{
public:
	DODSimulation(Renderer *Renderer, int AntCount);

	void Update(void) override;

	const char *GetName(void) override
	{
		return "DOD Simulation";
	}

private:
	std::vector<DODAnt> m_Ants;
};