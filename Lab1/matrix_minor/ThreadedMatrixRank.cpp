#include "stdafx.h"
#include <algorithm>
#include "ThreadedMatrixRank.h"

std::vector<unsigned> CThreadedMatrixRank::m_rang;

CThreadedMatrixRank::CThreadedMatrixRank(const CMatrix & matrix)
    : CMatrixAgregator(matrix)
{
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);

    m_threadsCount = sysinfo.dwNumberOfProcessors;
}

unsigned CThreadedMatrixRank::GetRang()
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

    auto result = std::max_element(m_rang.begin(), m_rang.end());
	if (result == m_rang.end())
	{
		return 0;
	}
	else
	{
		return *result;
	}
}

void CThreadedMatrixRank::SetThreadsCount(unsigned threadsCount)
{
    m_threadsCount = threadsCount;
}

DWORD CThreadedMatrixRank::CalculateSubMatrixRank(LPVOID qParam)
{
    dimensionPair pair = *((dimensionPair*)qParam);
    if (pair.first != nullptr)
    {
        CMatrix base = *(pair.first);
        unsigned dimension = pair.second;
        MatrixType subMatrix(dimension, std::vector<int>(dimension));
        for (size_t i = 0; i < (base.GetDimension() - (dimension - 1)); i++)
        {
            for (size_t j = 0; j < (base.GetDimension() - (dimension - 1)); j++)
            {
                for (size_t k = 0; k < dimension; k++)
                {
                    for (size_t n = 0; n < dimension; n++)
                    {
                        subMatrix[k][n] = base.GetMatrix()[i + k][j + n];
                    }
                }

                if (base.GetDeterminant(subMatrix) != 0)
                {
                    if (std::all_of(m_rang.begin(), m_rang.end(),
                        [=](unsigned cur) { return cur != dimension; }))
                    {
                        m_rang.push_back(dimension);
                    }
                }
            }
        }
    }

    ExitThread(0);
    return 0;
}
