#pragma once
#include "MatrixRankCalculator.h"

class CLinearMatrixRankCalculator : public CMatrixAgregator
{
public:
    CLinearMatrixRankCalculator(const CMatrix & matrix);

    unsigned GetRank() override;
};

