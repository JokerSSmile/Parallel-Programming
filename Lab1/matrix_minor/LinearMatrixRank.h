#pragma once
#include "MatrixAgregator.h"

class CLinearMatrixRank : public CMatrixAgregator
{
public:
    CLinearMatrixRank(const CMatrix & matrix);

    unsigned GetRang() override;
};

