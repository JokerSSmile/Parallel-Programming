#pragma once
#include "MatrixAgregator.h"

typedef std::pair<CMatrix*, unsigned> dimensionPair;

class CThreadedMatrixRank : public CMatrixAgregator
{
public:
    CThreadedMatrixRank(const CMatrix & matrix);

    unsigned GetRang() override;
    void SetThreadsCount(unsigned threadsCount);

private:
    static DWORD WINAPI CalculateSubMatrixRank(LPVOID qParam);

    static std::vector<unsigned> m_rang;
    unsigned m_threadsCount;
};
