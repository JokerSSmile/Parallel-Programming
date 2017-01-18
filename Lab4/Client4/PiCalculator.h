#pragma once
#include <ctime>

namespace calcuator
{
	int RandInt(int max)
	{
		return int(rand() % max);
	}

	float CalculatePi(size_t iterationsCount)
	{
		srand(time(0));
		int rad = 1000;
		int includedPoints = 0;
		for (auto i = 0; i < iterationsCount; ++i)
		{
			int x = RandInt(rad);
			int y = RandInt(rad);
			if (rad * rad >= x * x + y * y)
			{
				includedPoints++;
			}
		}

		return float(4.f * (float(includedPoints) / float(iterationsCount)));
	}
}