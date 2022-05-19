#pragma once
#include "Vector.h"

class CMatrix3x3
{
public:
	CMatrix3x3();
	CMatrix3x3(const CVector& angles);
	CMatrix3x3(double a11, double a12, double a13,
			double a21, double a22, double a23,
			double a31, double a32, double a33);

	void SetFromEuler(CVector angles);

	CMatrix3x3 operator*(const CMatrix3x3& other) const;
	CVector operator*(const CVector& other) const;

public:
	static CMatrix3x3 Identity;

private:
	double Matrix[3][3] =	{ { 1.0f, 0.0f, 0.0f }
							, { 0.0f, 1.0f, 0.0f }
							, { 0.0f, 0.0f, 1.0f } };

};

