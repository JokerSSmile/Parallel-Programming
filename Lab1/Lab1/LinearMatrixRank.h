#pragma once
#include "Matrix.h"

class LinearMatrixRank : public Matrix
{
public:
	LinearMatrixRank(const MatrixType& matrix);
	~LinearMatrixRank();

	int GetRank() override;
};

