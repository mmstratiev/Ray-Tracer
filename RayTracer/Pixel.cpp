#include "Pixel.h"

CPixel::CPixel(int x, int y)
	: X(x)
	, Y(y)
{}

CVector2D CPixel::GetCenter() const
{
	return CVector2D(X + 0.5, Y + 0.5);
}
