// DOD Sample
#include <OOD.Optimized\OODSimulation.Optimized.h>
#include <Common\Renderer.h>
#include <Common\Utils.h>

OODSimulationOptimized::OODSimulationOptimized(Renderer *Renderer, int AntCount) :
	Simulation(Renderer, AntCount),
	m_Ants(nullptr)
{
	m_Ants = reinterpret_cast<OODAntOptimized*>(malloc(sizeof(OODAntOptimized) * AntCount));

	for (int i = 0; i < AntCount; ++i)
	{
		new (&m_Ants[i]) OODAntOptimized(Utils::GetRandom(0, Utils::WIDTH, 0, Utils::HEIGHT));
	}
}

void OODSimulationOptimized::Update(void)
{
	for (int i = 0; i < GetAntCount(); ++i)
	{
		m_Ants[i].Update();
	}
}

void OODSimulationOptimized::Render(void)
{
	Renderer& ren = *GetRenderer();

	for (int i = 0; i < GetAntCount(); ++i)
	{
		m_Ants[i].Render(ren);
	}
}
