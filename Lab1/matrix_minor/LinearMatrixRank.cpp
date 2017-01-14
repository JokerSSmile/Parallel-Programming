#include "stdafx.h"
#include "LinearMatrixRank.h"

using namespace std;

CLinearMatrixRank::CLinearMatrixRank(const CMatrix & matrix) : CMatrixAgregator(matrix) {}

unsigned CLinearMatrixRank::GetRang()
{
	int rank = 0;
	size_t currentMatrixOrder = 1;
	size_t matrixSize = m_matrix.GetDimension();

	while (currentMatrixOrder <= matrixSize)
	{
		MatrixType tempMatrix(currentMatrixOrder, std::vector<int>(currentMatrixOrder));

		for (size_t i = 0; i < (matrixSize - (currentMatrixOrder - 1)); i++)
		{
			for (size_t j = 0; j < (matrixSize - (currentMatrixOrder - 1)); j++)
			{
				for (size_t k = 0; k < currentMatrixOrder; k++)
				{
					for (size_t n = 0; n < currentMatrixOrder; n++)
					{
						tempMatrix[k][n] = m_matrix.GetMatrix()[i + k][j + n];
					}
				}
				
				if (m_matrix.GetDeterminant(tempMatrix) != 0)
				{
					rank = currentMatrixOrder;
				}
			}
		}
		currentMatrixOrder++;

	}

	return rank;
}