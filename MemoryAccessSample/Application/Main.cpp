// DOD Sample
#include <memory>
#include <Common\Utils.h>
#include <functional>

typedef int ValueType;

const int KILO = 1000;
const int MEGA = KILO * 1000;
const int GIGA = MEGA * 1000;
const int KILOBYTE = 1024;
const int MEGABYTE = KILOBYTE * 1024;
const int GIGABYTE = MEGABYTE * 1024;
const int FUNCTION_CAL_COUNT = 10000;
const int64_t NUMBER_COUNT = GIGABYTE / sizeof(ValueType);
const uint64_t SIZE_IN_BYTE = NUMBER_COUNT * sizeof(ValueType);

uint64_t GetRDTSCOverhead(void)
{
	uint64_t avgRDTSC = 0;

	for (int i = 0; i < FUNCTION_CAL_COUNT; ++i)
	{
		uint64_t start = ReadTimeStampCounter();
		ReadTimeStampCounter();
		avgRDTSC += (ReadTimeStampCounter() - start) * 2;
	}

	return avgRDTSC / FUNCTION_CAL_COUNT;
}

uint64_t GetRandomIndexOverhead(void)
{
	uint64_t avgRDTSCCycle = GetRDTSCOverhead();

	uint64_t avgRDTSC = 0;

	for (int i = 0; i < FUNCTION_CAL_COUNT; ++i)
	{
		uint64_t start = ReadTimeStampCounter();
		int a = rand() % (i + 1);
		avgRDTSC += (ReadTimeStampCounter() - start);
	}

	return (avgRDTSC / FUNCTION_CAL_COUNT) - avgRDTSCCycle;
}

uint64_t RandomMemoryAccess(ValueType * Buffer)
{
	uint64_t rdtscOverhead = GetRDTSCOverhead();
	uint64_t randomIndexOverhead = GetRandomIndexOverhead();

	std::cout << "RandomMemoryAccess is Running" << std::endl;

	uint64_t startCycle = ReadTimeStampCounter();

	for (int64_t i = 0; i < NUMBER_COUNT; ++i)
	{
		int index = (rand() % NUMBER_COUNT) - 1;

		ValueType& value = Buffer[index];
		value++;
	}

	uint64_t endCycle = ReadTimeStampCounter();

	return (endCycle - startCycle) - rdtscOverhead - (randomIndexOverhead * NUMBER_COUNT);
}

uint64_t SequentialMemoryAccess(ValueType * Buffer)
{
	uint64_t rdtscOverhead = GetRDTSCOverhead();

	std::cout << "SequentialMemoryAccess is Running" << std::endl;

	uint64_t startCycle = ReadTimeStampCounter();

	for (int64_t i = 0; i < NUMBER_COUNT; ++i)
	{
		ValueType& value1 = Buffer[i];
		value1++;
	}

	uint64_t endCycle = ReadTimeStampCounter();

	return (endCycle - startCycle) - rdtscOverhead;
}

void Benchmark(std::function<uint64_t(ValueType*)> Function, ValueType * Buffer)
{
	static uint64_t cpuFreq = Utils::GetFrequency();

	uint64_t elapsedCycles = Function(Buffer);

	long double totalTimeInMillisec = elapsedCycles / (double)cpuFreq;
	long double eachByteInMillisec = (long double)totalTimeInMillisec / SIZE_IN_BYTE;
	long double megabytePerSecond = (1000 / eachByteInMillisec) / MEGABYTE;

	std::cout << "Cycles: " << (elapsedCycles / GIGA) << "G Time: " << totalTimeInMillisec << "ms Speed: " << megabytePerSecond << "mb/s" << std::endl << std::endl;
}

void main(void)
{
	std::cout << "ElementSize: " << sizeof(ValueType) << "b Count: " << NUMBER_COUNT << " Size: " << (SIZE_IN_BYTE / GIGABYTE) << "gb CPU-Freq.:" << (Utils::GetFrequency() / (float)MEGA) << "GHz" << std::endl << std::endl;

	ValueType * buffer = reinterpret_cast<ValueType*>(malloc(SIZE_IN_BYTE));
	memset(buffer, 0, SIZE_IN_BYTE);

	Benchmark(&RandomMemoryAccess, buffer);

	Benchmark(&SequentialMemoryAccess, buffer);

	system("pause");
}