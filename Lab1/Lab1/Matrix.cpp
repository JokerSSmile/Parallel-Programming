#include "stdafx.h"
#include "Matrix.h"


Matrix::Matrix(const MatrixType& matrix):
	m_matrix(matrix)
{
	m_demension = m_matrix.size();
	m_determinant = GetDeterminant(m_matrix);
}


Matrix::~Matrix()
{
}

double Matrix::GetDeterminant(MatrixType& matrix)
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

int Matrix::GetDemension()
{
	return m_demension;
}

MatrixType Matrix::GetMatrix()
{
	return m_matrix;
}

void Matrix::PrintMatrix(const MatrixType& matrix)
{
	for (size_t row = 0; row < matrix.size(); row++)
	{
		for (size_t column = 0; column < matrix.size(); column++)
		{
			cout << matrix[row][column] << "\t";
		}
		cout << endl;
	}
}
