#pragma once

typedef std::vector<std::vector<int>> MatrixType;

class CMatrix
{
public:
    CMatrix(const MatrixType & matrix) : m_matrix(matrix) {}

    size_t GetDimension();

    MatrixType & GetMatrix();
    double GetDeterminant(MatrixType & matrix);

private:
    MatrixType m_matrix;
};