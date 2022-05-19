#include <cmath>
#include <assert.h>

#include "Vector.h"
#include "Triangle.h"
#include "Utilities.h"

CVector::CVector()
{
}

CVector::CVector(double x, double y, double z)
	: X(x)
	, Y(y)
	, Z(z)
{}

double CVector::GetLength() const
{
	return std::sqrt(X * X + Y * Y + Z * Z);
}

CVector CVector::GetNormalized() const
{
	CVector result(*this);
	result.Normalize();
	return result;
}

void CVector::Normalize()
{
	double len = this->GetLength();
	if (!IsDoubleNearlyZero(len))
	{
		double invLen = 1.0f / this->GetLength();

		X *= invLen;
		Y *= invLen;
		Z *= invLen;
	}
}

CVector CVector::CrossProduct(const CVector& other) const
{
    return CVector::CrossProduct(*this, other);
}

double CVector::DotProduct(const CVector& other) const
{
    return CVector::DotProduct(*this, other);
}

CVector CVector::operator-() const
{
	return CVector(-X, -Y, -Z);
}

CVector CVector::operator-(const CVector& other) const
{
    return CVector(X - other.X, Y - other.Y, Z - other.Z);
}

CVector CVector::operator+(const CVector& other) const
{
    return CVector(X + other.X, Y + other.Y, Z + other.Z);
}

CVector& CVector::operator+=(const CVector& other)
{
	X += other.X;
	Y += other.Y;
	Z += other.Z;

	return *this;
}

CVector CVector::operator-(const double& other) const
{
	return CVector(X - other, Y - other, Z - other);
}

CVector CVector::operator+(const double& other) const
{
    return CVector(X + other, Y + other, Z + other);
}

CVector CVector::operator*(const double& other) const
{
    return CVector(X * other, Y * other, Z * other);
}

CVector CVector::CrossProduct(const CVector& v1, const CVector& v2)
{
	return CVector	( v1.Y * v2.Z - v1.Z * v2.Y
					, v1.Z * v2.X - v1.X * v2.Z
					, v1.X * v2.Y - v1.Y * v2.X );
}

double CVector::DotProduct(const CVector& v1, const CVector& v2)
{
    double product = 0.0f;
    product += v1.X * v2.X;
    product += v1.Y * v2.Y;
    product += v1.Z * v2.Z;
    return product;
}

std::ostream& operator<<(std::ostream& os, const CVector& vector)
{
	return os << "(" << vector.X << ", " <<vector.Y << ", " << vector.Z << ")";
}
