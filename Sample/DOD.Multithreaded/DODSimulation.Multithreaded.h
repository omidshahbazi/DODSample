// DOD Sample
#pragma once
#include <DOD\DODSimulation.h>
#include <atomic>
#include <thread>

class DODSimulationMultithreaded : public DODSimulation
{
private:
	const int THREAD_COUNT = 10;

	struct UpdateInfo
	{
	public:
		DODAntData* Ants;
		int Count;
		std::atomic<bool> ReadyToStart;
		std::atomic<bool> IsDone;
	};

public:
	DODSimulationMultithreaded(Renderer* Renderer, int AntCount);

	virtual void Update(void) override;

	const char* GetName(void) override
	{
		return "DOD Multithreaded Simulation";
	}

private:
	static void UpdateThreadWorker(UpdateInfo* Info);

private:
	UpdateInfo* m_UpdateInfos;
	std::thread* m_Threads;
};