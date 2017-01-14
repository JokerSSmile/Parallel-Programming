#include "stdafx.h"
#include "LinearMatrixRankCalculator.h"

using namespace std;

CLinearMatrixRankCalculator::CLinearMatrixRankCalculator(const CMatrix & matrix) : CMatrixAgregator(matrix) {}

unsigned CLinearMatrixRankCalculator::GetRank()
{
	int rank = 0;
	size_t currentMatrixOrder = 1;
	size_t matrixSize = m_matrix.GetDimension();

	while (currentMatrixOrder <= matrixSize)
	{

		DoTheAlghorithm(currentMatrixOrder, matrixSize, m_matrix, [&rank, currentMatrixOrder] {
			rank = currentMatrixOrder;
		});
		
	}

	return rank;
}