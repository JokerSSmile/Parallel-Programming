#pragma once

class Matrix
{
public:

	Matrix(const MatrixType& matrix);
	~Matrix();

	double GetDeterminant(MatrixType& matrix);
	int virtual GetRank() = 0;
	int GetDemension();
	MatrixType GetMatrix();
	void PrintMatrix(const MatrixType& matrix);

private:

	int m_demension;
	double m_determinant;
	MatrixType m_matrix;
};

