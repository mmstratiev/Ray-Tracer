#pragma once
#include "Vector2D.h"

class CPixel
{
public:
	CPixel(int x, int y);

	CVector2D GetCenter() const;

public:
	int X = 0;
	int Y = 0;
};

