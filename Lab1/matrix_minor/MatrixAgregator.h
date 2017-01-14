#pragma once
#include "matrix.h"

class CMatrixAgregator
{
public:
    virtual unsigned GetRang() = 0;

protected:
    CMatrixAgregator(const CMatrix & matrix) : m_matrix(matrix) {}
    CMatrix m_matrix;
};