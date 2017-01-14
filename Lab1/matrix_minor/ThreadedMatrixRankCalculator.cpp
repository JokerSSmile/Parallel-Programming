#include "stdafx.h"
#include <algorithm>
#include "ThreadedMatrixRankCalculator.h"

std::vector<unsigned> CThreadedMatrixRankCalculator::m_rank;

CThreadedMatrixRankCalculator::CThreadedMatrixRankCalculator(const CMatrix & matrix)
    : CMatrixAgregator(matrix)
{
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);

    m_threadsCount = sysinfo.dwNumberOfProcessors;
}

unsigned CThreadedMatrixRankCalculator::GetRank()
{
	std::vector<DWORD> threadId(m_threadsCount);
    HANDLE *threadsHandles = new HANDLE[m_threadsCount];
	std::vector<dimensionPair> lpParameters;
    for (unsigned dimension = 1; dimension < m_matrix.GetDimension(); dimension++)
    {
        lpParameters.emplace_back(std::make_pair(&m_matrix, dimension));
    }

    for (size_t triggerIndex = 0, currentThreadCount = 0; triggerIndex < m_matrix.GetDimension();)
    {
        if (currentThreadCount < m_threadsCount)
        {
            threadsHandles[currentThreadCount] = CreateThread(NULL, 0, CalculateSubMatrixRank, (LPVOID)&lpParameters[triggerIndex], 0, &threadId[currentThreadCount]);
            currentThreadCount++;
            triggerIndex++;
        }
        else
        {
            WaitForMultipleObjects(m_threadsCount, threadsHandles, true, INFINITE);
            currentThreadCount = 0;
        }
    }

    WaitForMultipleObjects(m_threadsCount, threadsHandles, true, INFINITE);
    delete[] threadsHandles;

    auto result = std::max_element(m_rank.begin(), m_rank.end());
	if (result == m_rank.end())
	{
		return 0;
	}
	else
	{
		return *result;
	}
}

void CThreadedMatrixRankCalculator::SetThreadsCount(unsigned threadsCount)
{
    m_threadsCount = threadsCount;
}

DWORD CThreadedMatrixRankCalculator::CalculateSubMatrixRank(LPVOID qParam)
{
    dimensionPair pair = *((dimensionPair*)qParam);
    if (pair.first != nullptr)
    {
        CMatrix base = *(pair.first);
        size_t dimension = pair.second;

		size_t baseDimension = base.GetDimension();

		DoTheAlghorithm(dimension, baseDimension, base, [dimension] {

			if (std::all_of(m_rank.begin(), m_rank.end(),
				[=](unsigned cur) { return cur != dimension; }))
			{
				m_rank.push_back(dimension);
			}
		});
    }

    ExitThread(0);
    return 0;
}
