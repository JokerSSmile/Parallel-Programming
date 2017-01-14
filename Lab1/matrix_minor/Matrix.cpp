#include "stdafx.h"
#include "matrix.h"
#include <iostream>
#include <fstream>

using namespace std;

size_t CMatrix::GetDimension()
{
    return m_matrix.size();
}

MatrixType & CMatrix::GetMatrix()
{
    return m_matrix;
}

double CMatrix::GetDeterminant(MatrixType & matrix)
{
	double det = 1;
	size_t matrixSize = matrix.size();

	for (size_t i = 0; i < matrixSize; ++i)
	{
		size_t k = i;
		for (size_t j = i + 1; j < matrixSize; ++j)
		{
			if (abs(matrix[j][i]) > abs(matrix[k][i]))
			{
				k = j;
			}
		}

		if (abs(matrix[k][i]) < DBL_EPSILON)
		{
			det = 0;
			break;
		}
		std::swap(matrix[i], matrix[k]);

		if (i != k)
		{
			det = -det;
		}

		det *= matrix[i][i];
		for (size_t j = i + 1; j < matrixSize; ++j)
		{
			matrix[i][j] /= matrix[i][i];
		}
		for (size_t j = 0; j<matrixSize; ++j)
		{
			if (j != i && abs(matrix[j][i]) > DBL_EPSILON)
			{
				for (size_t k = i + 1; k < matrixSize; ++k)
				{
					matrix[j][k] -= matrix[i][k] * matrix[j][i];
				}
			}
		}
	}

	return det;
}