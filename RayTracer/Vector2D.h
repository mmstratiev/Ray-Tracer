#pragma once
class CVector2D
{
public:
	CVector2D();
	CVector2D(double x, double y);

	CVector2D operator/(const CVector2D& other);
	CVector2D& operator/=(const CVector2D& other);

public:
	double X = 0.0f;
	double Y = 0.0f;
};

