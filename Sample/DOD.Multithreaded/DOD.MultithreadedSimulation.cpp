// DOD Sample
#include <DOD.Multithreaded\DOD.MultithreadedSimulation.h>
#include <Common\Renderer.h>
#include <Common\Utils.h>
#include <future>

void DODMultithreadedSimulation::Update(void)
{
	DODAntData *antsData = &m_AntsData[0];

	const int DIVISION_COUNT = 5;
	const int PROCESS_COUNT = GetAntCount() / DIVISION_COUNT;

	for (int i = 0; i < DIVISION_COUNT; ++i)
		std::async([&]() { DODAntsLogic::Update(antsData, PROCESS_COUNT * i, PROCESS_COUNT); });

	DODAntsLogic::Render(antsData, GetAntCount(), GetRenderer());
}