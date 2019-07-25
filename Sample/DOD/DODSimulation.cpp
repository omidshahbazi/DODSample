// DOD Sample
#include <DOD\DODSimulation.h>
#include <Common\Renderer.h>

DODSimulation::DODSimulation(Renderer *Renderer, int AntCount) :
	Simulation(Renderer, AntCount)
{
	for (int i = 0; i < AntCount; ++i)
	{
		DODAnt ant;
		ant.Position = GetRandom(0, 100, 0, 100);

		m_Ants.push_back(ant);
	}
}

void DODSimulation::Update(void)
{
	DODAnt *ants = &m_Ants[0];

	DODAntsLogic::UpdateDODAnts(ants, GetAntCount());

	DODAntsLogic::RenderDODAnts(ants, GetAntCount(), GetRenderer());
}