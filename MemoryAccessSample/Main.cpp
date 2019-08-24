// DOD Sample
#include <memory>
#include <Common\Utils.h>

const long NUMBER_COUNT = 1024 * 1024 * 1024;

void RandomMemoryAccess(int *Buffer)
{
	long traverseLen = NUMBER_COUNT / 2;

	for (long i = 0; i < traverseLen; ++i)
	{
		int& value1 = Buffer[i];
		value1++;

		int& value2 = Buffer[(NUMBER_COUNT - 1) - i];
		value2++;
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
	BEGIN_PROFILE("Allocation");
	const long long SIZE_IN_BYTE = NUMBER_COUNT * sizeof(int);
	int* buffer = reinterpret_cast<int*>(malloc(SIZE_IN_BYTE));
	memset(buffer, 0, SIZE_IN_BYTE);
	END_PROFILE("Allocation");

	RandomMemoryAccess(buffer);

	SequentialMemoryAccess(buffer);
}