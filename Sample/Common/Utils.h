// DOD Sample
#pragma once
#include <Windows.h>

class Utils
{
public:
	static long GetFrequency(void)
	{
		LARGE_INTEGER var;
		QueryPerformanceFrequency(&var);
		return var.QuadPart;
	}

	static float GetTimestamp(void)
	{
		static long frequency = GetFrequency();

		LARGE_INTEGER clock;
		QueryPerformanceCounter(&clock);

		return (float(clock.QuadPart * 1000000) / frequency) / 1000000;
	}

	static float GetTime(void)
	{
		static float start = GetTimestamp();

		return GetTimestamp() - start;
	}

};