// DOD Sample
#include <DOD.Multithreaded\DODSimulation.Multithreaded.h>
#include <Common\Renderer.h>
#include <Common\Utils.h>

DODSimulationMultithreaded::DODSimulationMultithreaded(Renderer* Renderer, int AntCount) :
	DODSimulation(Renderer, AntCount),
	m_UpdateInfos(nullptr),
	m_Threads(nullptr)
{
	m_UpdateInfos = reinterpret_cast<UpdateInfo*>(malloc(sizeof(UpdateInfo) * THREAD_COUNT));
	m_Threads = reinterpret_cast<std::thread*>(malloc(sizeof(std::thread) * THREAD_COUNT));

	const int PROCESS_COUNT = AntCount / THREAD_COUNT;

	for (int i = 0; i < THREAD_COUNT; ++i)
	{
		UpdateInfo& updateInfo = m_UpdateInfos[i];
		updateInfo.Ants1 = &m_AntsData1[i * PROCESS_COUNT];
		updateInfo.Ants2 = &m_AntsData2[i * PROCESS_COUNT];
		updateInfo.Count = PROCESS_COUNT;
		updateInfo.IsDone = true;
		updateInfo.ReadyToStart = false;

		new (&m_Threads[i]) std::thread(UpdateThreadWorker, &updateInfo);
	}
}

void DODSimulationMultithreaded::Update(void)
{
	for (int i = 0; i < THREAD_COUNT; ++i)
		m_UpdateInfos[i].ReadyToStart.exchange(true);

	bool isFinished = true;
	do
	{
		Sleep(1);

		isFinished = true;

		for (int i = 0; i < THREAD_COUNT; ++i)
			isFinished &= m_UpdateInfos[i].IsDone.load();

	} while (!isFinished);
}

void DODSimulationMultithreaded::UpdateThreadWorker(UpdateInfo * Info)
{
	while (true)
	{
		if (!Info->ReadyToStart.load())
		{
			Sleep(1);
			continue;
		}

		Info->ReadyToStart.exchange(false);

		DODAntsLogic::Update(Info->Ants1, Info->Ants2, 0, Info->Count);

		Info->IsDone.exchange(true);
	}
}
