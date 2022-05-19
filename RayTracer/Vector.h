#pragma once

#include <iostream>
#include <vector>

class CTriangle;
class CVector
{
public:
	CVector();
	CVector(double x, double y, double z);

	double	GetLength() const;
	CVector GetNormalized() const;

	void	Normalize();
	CVector	CrossProduct(const CVector& other) const;
	double	DotProduct(const CVector& other) const;

	CVector operator-() const;
	CVector operator-(const CVector& other) const;
	CVector operator+(const CVector& other) const;
	CVector& operator+=(const CVector& other);

	CVector operator-(const double& other) const;
	CVector operator+(const double& other) const;
	CVector operator*(const double& other) const;
	friend std::ostream& operator<<(std::ostream& os, const CVector& vector);

	static CVector	CrossProduct(const CVector& v1, const CVector& v2);
	static double	DotProduct(const CVector& v1, const CVector& v2);

public:
	double X = 0.0f;
	double Y = 0.0f;
	double Z = 0.0f;
};

