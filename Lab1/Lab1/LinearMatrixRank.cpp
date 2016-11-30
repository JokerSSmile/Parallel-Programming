#include "stdafx.h"
#include "LinearMatrixRank.h"

LinearMatrixRank::LinearMatrixRank(const MatrixType& matrix):
	Matrix(matrix)
{
}


LinearMatrixRank::~LinearMatrixRank()
{
}

int LinearMatrixRank::GetRank()
{
	
	int rank = 0;
	size_t currentMatrixOrder = 1;
	size_t matrixSize = GetDemension();
	
	while (currentMatrixOrder <= matrixSize)
	{
		MatrixType tempMatrix(currentMatrixOrder, std::vector<double>(currentMatrixOrder));

		for (size_t a = 0; a < (matrixSize - (currentMatrixOrder - 1)); a++)
		{
			for (size_t b = 0; b < (matrixSize - (currentMatrixOrder - 1)); b++)
			{
				for (size_t c = 0; c < currentMatrixOrder; c++)
				{
					for (size_t d = 0; d < currentMatrixOrder; d++)
					{
						tempMatrix[c][d] = GetMatrix()[a + c][b + d];
					}
				}
				PrintMatrix(tempMatrix);
				cout << endl;
				if (GetDeterminant(tempMatrix) != 0)
				{
					rank = currentMatrixOrder;
				}
			}
		}
		currentMatrixOrder++;
		
	}
	
	return rank;
}
