// DOD Sample
#pragma once
#include <Windows.h>
#include <random>
#include <Common\Vector2.h>
#include <iostream>

class Utils
{
public:
	static const int WIDTH = 800;
	static const int HEIGHT = 600;
	static const int MIN_STEP_COUNT = 100;
	static const int MAX_STEP_COUNT = 400;
	static const int ANT_COUNT = 1000000;

public:
	static uint64_t GetCycle(void)
	{
		return __rdtsc();
	}

	static __int64 GetFrequency(void)
	{
		static LARGE_INTEGER var;
		QueryPerformanceFrequency(&var);
		return var.QuadPart;
	}

	static __int64 GetClock(void)
	{
		static LARGE_INTEGER clock;
		QueryPerformanceCounter(&clock);
		return clock.QuadPart;
	}

	static float GetTimestamp(void)
	{
		static __int64 frequency = GetFrequency();

		static __int64 clock = 0;
		clock = GetClock();

		return (float(clock * 1000000) / frequency) / 1000000;
	}

	static float GetTime(void)
	{
		static float start = GetTimestamp();

		return GetTimestamp() - start;
	}

	static float GetRandom(float Min, float Max)
	{
		return Min + (rand() % (int)(Max - Min));
	}

	static int GetRandom(int Min, int Max)
	{
		return Min + (rand() % (int)(Max - Min));
	}

	static Vector2F GetRandom(float MinX, float MaxX, float MinY, float MaxY)
	{
		return { GetRandom(MinX, MaxX), GetRandom(MinY, MaxY) };
	}

	static void PrintProfile(const char *Name, uint64_t Cycles, __int64 Clock)
	{
		std::cout << Name << "\t\t" << Cycles << "\t\t" << (double)(Clock * 1000.0F / GetFrequency()) << std::endl;
		std::cout << "------------------------------------------------" << std::endl;
	}
};

#define PRINT_PROFILER_TABLE_COLUMN() \
	std::cout << "Place\t\tCycle\t\tTime(ms)" << std::endl; \
	std::cout << "================================================" << std::endl;

#define BEGIN_PROFILE(Name) \
	__int64 __BeginClock__##Name = Utils::GetClock(); \
	uint64_t __BeginCycle__##Name = Utils::GetCycle();

#define END_PROFILE(Name) \
	uint64_t __TotalCycle__##Name = Utils::GetCycle() - __BeginCycle__##Name; \
	__int64 __TotalClock__##Name = Utils::GetClock() - __BeginClock__##Name; \
	Utils::PrintProfile(#Name, __TotalCycle__##Name, __TotalClock__##Name);

#define BEGIN_PROFILE_COLLECTOR(Name) \
	uint64_t __CollectorSampleCount__##Name = 0; \
	uint64_t __CollectorTotalCycle__##Name = 0; \
	uint64_t __CollectorBeginCycle__##Name = 0; \
	uint64_t __CollectorTotalClock__##Name = 0; \
	uint64_t __CollectorBeginClock__##Name = 0;

#define BEGIN_PROFILE_COLLECT(Name) \
	uint64_t __CollectorBeginCycle__##Name = Utils::GetCycle(); \
	__int64 __CollectorBeginClock__##Name = Utils::GetClock();

#define END_PROFILE_COLLECT(Name) \
	__CollectorTotalCycle__##Name += Utils::GetCycle() - __CollectorBeginCycle__##Name; \
	__CollectorTotalClock__##Name += Utils::GetClock() - __CollectorBeginClock__##Name; \
	__CollectorSampleCount__##Name++;

#define END_PROFILE_COLLECTOR(Name) \
	Utils::PrintProfile(#Name, __CollectorTotalCycle__##Name / __CollectorSampleCount__##Name, __CollectorTotalClock__##Name / __CollectorSampleCount__##Name);