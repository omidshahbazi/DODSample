// DOD Sample
#include <DOD\DODSimulation.h>
#include <Common\Renderer.h>
#include <Common\Utils.h>

DODSimulation::DODSimulation(Renderer *Renderer, int AntCount) :
	Simulation(Renderer, AntCount),
	m_AntsData(nullptr)
{
	m_AntsData = reinterpret_cast<DODAntData*>(malloc(sizeof(DODAntData) * AntCount));

	for (int i = 0; i < AntCount; ++i)
	{
		DODAntData &data = m_AntsData[i];

		data.Position = Utils::GetRandom(0, Utils::WIDTH, 0, Utils::HEIGHT);
		DODAntsLogic::FindNewTarget(data);
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
