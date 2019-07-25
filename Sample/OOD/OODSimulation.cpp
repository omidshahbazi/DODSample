// DOD Sample
#include <OOD\OODSimulation.h>
#include <Common\Renderer.h>

OODSimulation::OODSimulation(Renderer *Renderer, int AntCount) :
	Simulation(Renderer, AntCount)
{
	for (int i = 0; i < AntCount; ++i)
	{
		OODAnt *ant = new OODAnt(GetRandom(0, 100, 0, 100));

		m_Ants.push_back(ant);
	}
}

void OODSimulation::Update(void)
{
	for (int i = 0; i < GetAntCount(); ++i)
	{
		OODAnt *ant = m_Ants[i];

		ant->Update();

		ant->Render(GetRenderer());
	}
}