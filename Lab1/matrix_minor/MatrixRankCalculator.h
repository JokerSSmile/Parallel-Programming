#pragma once
#include "matrix.h"

class CMatrixAgregator
{
public:
    virtual unsigned GetRank() = 0;

	template <typename T>
	static void DoTheAlghorithm(size_t& dimension, size_t matrixSize, CMatrix matrix, T& rank);

protected:
    CMatrixAgregator(const CMatrix & matrix) : m_matrix(matrix) {}
    CMatrix m_matrix;
};

template <typename T>
static void CMatrixAgregator::DoTheAlghorithm(size_t& dimension, size_t matrixSize, CMatrix matrix, T& callback)
{
	MatrixType tempMatrix(dimension, std::vector<int>(dimension));

	for (size_t i = 0; i < (matrixSize - (dimension - 1)); i++)
	{
		for (size_t j = 0; j < (matrixSize - (dimension - 1)); j++)
		{
			for (size_t k = 0; k < dimension; k++)
			{
				for (size_t n = 0; n < dimension; n++)
				{
					tempMatrix[k][n] = matrix.GetMatrix()[i + k][j + n];
				}
			}

			if (matrix.GetDeterminant(tempMatrix) != 0)
			{
				callback();
			}
		}
	}
	dimension++;
}