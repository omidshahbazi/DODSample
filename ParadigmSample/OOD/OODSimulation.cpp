// DOD Sample
#include <OOD\OODSimulation.h>
#include <Common\Renderer.h>
#include <Common\Utils.h>

OODSimulation::OODSimulation(Renderer *Renderer, int AntCount) :
	Simulation(Renderer, AntCount)
{
	for (int i = 0; i < AntCount; ++i)
	{
		OODAnt *ant = new OODAnt(Utils::GetRandom(0, Utils::WIDTH, 0, Utils::HEIGHT));

		m_Ants.push_back(ant);
	}
}

void OODSimulation::Update(void)
{
	for (int i = 0; i < GetAntCount(); ++i)
	{
		m_Ants[i]->Update();
	}
}

void OODSimulation::Render(void)
{
	for (int i = 0; i < GetAntCount(); ++i)
	{
		m_Ants[i]->Render(GetRenderer());
	}
}
