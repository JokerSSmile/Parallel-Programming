#pragma once
#include "MatrixRankCalculator.h"

typedef std::pair<CMatrix*, unsigned> dimensionPair;

class CThreadedMatrixRankCalculator : public CMatrixAgregator
{
public:
    CThreadedMatrixRankCalculator(const CMatrix & matrix);

    unsigned GetRank() override;
    void SetThreadsCount(unsigned threadsCount);

private:
    static DWORD WINAPI CalculateSubMatrixRank(LPVOID qParam);

    static std::vector<unsigned> m_rank;
    unsigned m_threadsCount;
};