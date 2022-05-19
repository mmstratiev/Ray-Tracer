#include "Vector2D.h"

CVector2D::CVector2D()
{
}

CVector2D::CVector2D(double x, double y)
	: X(x)
	, Y(y)
{}

CVector2D CVector2D::operator/(const CVector2D& other)
{
	return CVector2D(X / other.X, Y / other.Y);
}

CVector2D& CVector2D::operator/=(const CVector2D& other)
{
	X /= other.X;
	Y /= other.Y;
	return *this;
}
