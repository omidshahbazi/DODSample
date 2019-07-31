// DOD Sample
#include <DOD\DODSimulation.h>
#include <Common\Renderer.h>
#include <Common\Utils.h>

DODSimulation::DODSimulation(Renderer *Renderer, int AntCount) :
	Simulation(Renderer, AntCount)
{
	for (int i = 0; i < AntCount; ++i)
	{
		DODAntData data;

		data.Position = Utils::GetRandom(0, Utils::WIDTH, 0, Utils::HEIGHT);
		DODAntsLogic::FindNewTarget(data);

		m_AntsData.push_back(data);
	}
}

void DODSimulation::Update(void)
{
	DODAntsLogic::Update(&m_AntsData[0], 0, GetAntCount());
}

void DODSimulation::Render(void)
{
	DODAntsLogic::Render(&m_AntsData[0], GetAntCount(), GetRenderer());
}
