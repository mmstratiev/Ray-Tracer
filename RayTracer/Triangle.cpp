#include "Triangle.h"

CTriangle::CTriangle()
{
}

CTriangle::CTriangle(CVector a, CVector b, CVector c)
	: Vertices {a, b, c}
{}

const CVector& CTriangle::GetV0() const
{
	return Vertices[0];
}

const CVector& CTriangle::GetV1() const
{
	return Vertices[1];
}

const CVector& CTriangle::GetV2() const
{
	return Vertices[2];
}

CVector CTriangle::GetNormal() const
{
	return CVector::CrossProduct(Vertices[1] - Vertices[0], Vertices[2] - Vertices[0]).GetNormalized();
}

double CTriangle::GetPerimeter() const
{
	return Vertices[0].GetLength() + Vertices[1].GetLength() + Vertices[2].GetLength();
}

double CTriangle::GetArea() const
{
	// Heron's formula - https://en.wikipedia.org/wiki/Heron%27s_formula
	double semiP = this->GetPerimeter() / 2.0f;
	return sqrt	(semiP
				* (semiP - Vertices[0].GetLength())
				* (semiP - Vertices[1].GetLength())
				* (semiP - Vertices[2].GetLength()));
	return 0.0;
}
