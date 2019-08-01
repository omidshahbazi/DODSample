// DOD Sample
#include <DOD.Multithreaded\DODSimulation.Multithreaded.h>
#include <Common\Renderer.h>
#include <Common\Utils.h>
#include <future>

void DODSimulationMultithreaded::Update(void)
{
	DODAntData *antsData = &m_AntsData[0];

	const int DIVISION_COUNT = 20;
	const int PROCESS_COUNT = GetAntCount() / DIVISION_COUNT;

	for (int i = 0; i < DIVISION_COUNT; ++i)
		std::async([&]() { DODAntsLogic::Update(antsData, PROCESS_COUNT * i, PROCESS_COUNT); });
}