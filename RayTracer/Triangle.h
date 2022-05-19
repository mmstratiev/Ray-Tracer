#pragma once

#include "Vector.h"
#include "RGBColor.h"

class CTriangle
{
public:
	CTriangle();
	CTriangle(CVector a, CVector b, CVector c);

	const CVector& GetV0() const;
	const CVector& GetV1() const;
	const CVector& GetV2() const;

	CVector		GetNormal() const;
	double		GetPerimeter() const;
	double		GetArea() const;

private:
	CVector		Vertices[3];
};

