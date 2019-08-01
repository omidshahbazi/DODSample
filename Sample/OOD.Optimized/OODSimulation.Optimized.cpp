// DOD Sample
#include <OOD.Optimized\OODSimulation.Optimized.h>
#include <Common\Renderer.h>
#include <Common\Utils.h>

OODSimulationOptimized::OODSimulationOptimized(Renderer *Renderer, int AntCount) :
	Simulation(Renderer, AntCount)
{
	for (int i = 0; i < AntCount; ++i)
	{
		OODAntOptimized *ant = new OODAntOptimized(Utils::GetRandom(0, Utils::WIDTH, 0, Utils::HEIGHT));

		m_Ants.push_back(ant);
	}
}

void OODSimulationOptimized::Update(void)
{
	for (int i = 0; i < GetAntCount(); ++i)
	{
		m_Ants[i]->Update();
	}
}

void OODSimulationOptimized::Render(void)
{
	for (int i = 0; i < GetAntCount(); ++i)
	{
		m_Ants[i]->Render(GetRenderer());
	}
}
