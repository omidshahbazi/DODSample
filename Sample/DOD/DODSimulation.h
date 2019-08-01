// DOD Sample
#pragma once
#include <Common\Simulation.h>
#include <DOD\DODAnt.h>
#include <vector>

class DODSimulation : public Simulation
{
public:
	DODSimulation(Renderer *Renderer, int AntCount);

	virtual void Update(void) override;

	virtual void Render(void) override;

	const char *GetName(void) override
	{
		return "DOD Simulation";
	}

protected:
	std::vector<DODAntData> m_AntsData;
};