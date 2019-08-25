// DOD Sample
#include <memory>
#include <Common\Utils.h>

const long FUNCTION_CAL_COUNT = 1024;
const __int64 NUMBER_COUNT = 1024 * 1024 * 1024;

int GetRDTSC_Cycles(void)
{
	uint64_t avgRDTSC = 0;

	for (int i = 0; i < FUNCTION_CAL_COUNT; ++i)
	{
		uint64_t start = Utils::GetCycle();
		Utils::GetCycle();
		avgRDTSC += (Utils::GetCycle() - start) * 2;
	}

	return avgRDTSC / FUNCTION_CAL_COUNT;
}

int GetRand_Cycles(void)
{
	uint64_t avgRDTSCCycle = GetRDTSC_Cycles();

	uint64_t avgRDTSC = 0;

	for (int i = 0; i < FUNCTION_CAL_COUNT; ++i)
	{
		uint64_t start = Utils::GetCycle();
		int a = rand() % (i + 1);
		avgRDTSC += (Utils::GetCycle() - start) - avgRDTSCCycle;
	}

	return avgRDTSC / FUNCTION_CAL_COUNT;
}

void RandomMemoryAccess(int* Buffer)
{
	for (long i = 0; i < NUMBER_COUNT; ++i)
	{
		int index = (rand() % NUMBER_COUNT) - 1;

		int& value = Buffer[index];
		value++;
	}
}

void SequentialMemoryAccess(int* Buffer)
{
	for (long i = 0; i < NUMBER_COUNT; ++i)
	{
		int& value1 = Buffer[i];
		value1++;
	}
}

void main(void)
{
	int avgRDTSCCycle = GetRDTSC_Cycles();
	int avgRandomCycle = GetRand_Cycles();

	__int64 cpuFreq = Utils::GetFrequency();



	const long long SIZE_IN_BYTE = NUMBER_COUNT * sizeof(int);

	int* buffer = reinterpret_cast<int*>(malloc(SIZE_IN_BYTE));
	memset(buffer, 0, SIZE_IN_BYTE);

	uint64_t start = Utils::GetClock();
	RandomMemoryAccess(buffer);
	float totalTime = ((Utils::GetClock() - start) - avgRDTSCCycle - (avgRandomCycle * NUMBER_COUNT)) / (float)cpuFreq;

	start = Utils::GetClock();
	SequentialMemoryAccess(buffer);
	totalTime = ((Utils::GetClock() - start) - avgRDTSCCycle) / (float)cpuFreq;
}