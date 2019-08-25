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
	static const int MIN_STEP_COUNT = 2;
	static const int MAX_STEP_COUNT = 20;
	static const int ANT_COUNT = 1000000;

public:
	static __forceinline int64_t GetFrequency(void)
	{
		static LARGE_INTEGER var;
		QueryPerformanceFrequency(&var);
		return var.QuadPart;
	}

	static __forceinline int64_t GetClock(void)
	{
		static LARGE_INTEGER clock;
		QueryPerformanceCounter(&clock);
		return clock.QuadPart;
	}

	static __forceinline float GetTimestamp(void)
	{
		static int64_t frequency = GetFrequency();

		static int64_t clock = 0;
		clock = GetClock();

		return (float(clock * 1000000) / frequency) / 1000000;
	}

	static __forceinline float GetTime(void)
	{
		static float start = GetTimestamp();

		return GetTimestamp() - start;
	}

	static __forceinline float GetRandom(float Min, float Max)
	{
		return Min + (rand() % (int)(Max - Min));
	}

	static __forceinline int GetRandom(int Min, int Max)
	{
		return Min + (rand() % (int)(Max - Min));
	}

	static __forceinline Vector2F GetRandom(float MinX, float MaxX, float MinY, float MaxY)
	{
		return { GetRandom(MinX, MaxX), GetRandom(MinY, MaxY) };
	}

	static __forceinline void PrintProfile(const char *Name, uint64_t Cycles, int64_t Clock)
	{
		double time = (double)(Clock * 1000.0F / GetFrequency());
		std::cout << Name << "\t\t" << time << "\t\t" << (time / ANT_COUNT) << std::endl; //"\t\t" << Cycles <<
		std::cout << "------------------------------------------------" << std::endl;
	}
};

//\t\tCycle
#define PRINT_PROFILER_TABLE_COLUMN() \
	std::cout << "Place\t\tTime(ms)\tTime/Ant(ms)" << std::endl; \
	std::cout << "================================================" << std::endl;

#define BEGIN_PROFILE(Name) \
	int64_t __BeginClock__##Name = Utils::GetClock(); \
	uint64_t __BeginCycle__##Name = ReadTimeStampCounter();

#define END_PROFILE(Name) \
	uint64_t __TotalCycle__##Name = ReadTimeStampCounter() - __BeginCycle__##Name; \
	int64_t __TotalClock__##Name = Utils::GetClock() - __BeginClock__##Name; \
	Utils::PrintProfile(#Name, __TotalCycle__##Name, __TotalClock__##Name);

#define BEGIN_PROFILE_COLLECTOR(Name) \
	uint64_t __CollectorSampleCount__##Name = 0; \
	uint64_t __CollectorTotalCycle__##Name = 0; \
	uint64_t __CollectorBeginCycle__##Name = 0; \
	uint64_t __CollectorTotalClock__##Name = 0; \
	uint64_t __CollectorBeginClock__##Name = 0;

#define BEGIN_PROFILE_COLLECT(Name) \
	uint64_t __CollectorBeginCycle__##Name = ReadTimeStampCounter(); \
	int64_t __CollectorBeginClock__##Name = Utils::GetClock();

#define END_PROFILE_COLLECT(Name) \
	__CollectorTotalCycle__##Name += ReadTimeStampCounter() - __CollectorBeginCycle__##Name; \
	__CollectorTotalClock__##Name += Utils::GetClock() - __CollectorBeginClock__##Name; \
	__CollectorSampleCount__##Name++;

#define END_PROFILE_COLLECTOR(Name) \
	Utils::PrintProfile(#Name, __CollectorTotalCycle__##Name / __CollectorSampleCount__##Name, __CollectorTotalClock__##Name / __CollectorSampleCount__##Name);