// DOD Sample
#include <DOD\DODSimulation.h>
#include <Common\Renderer.h>
#include <Common\Utils.h>

DODSimulation::DODSimulation(Renderer *Renderer, int AntCount) :
	Simulation(Renderer, AntCount),
	m_AntsData1(nullptr),
	m_AntsData2(nullptr)
{
	m_AntsData1 = reinterpret_cast<DODAntData1*>(malloc(sizeof(DODAntData1) * AntCount));
	m_AntsData2 = reinterpret_cast<DODAntData2*>(malloc(sizeof(DODAntData2) * AntCount));

	for (int i = 0; i < AntCount; ++i)
	{
		DODAntData1 &data1 = m_AntsData1[i];
		DODAntData2 &data2 = m_AntsData2[i];

		data2.Position = Utils::GetRandom(0, Utils::WIDTH, 0, Utils::HEIGHT);
		DODAntsLogic::FindNewTarget(data1, data2);
	}
}

void DODSimulation::Update(void)
{
	DODAntsLogic::Update(&m_AntsData1[0], &m_AntsData2[0], 0, GetAntCount());
}

void DODSimulation::Render(void)
{
	DODAntsLogic::Render(&m_AntsData2[0], GetAntCount(), GetRenderer());
}
