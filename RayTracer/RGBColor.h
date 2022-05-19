#pragma once

#include <iostream>

class CRGBColor
{
public:
	CRGBColor();

	// 0 to 255
	CRGBColor(int r, int g, int b);
	
	// 0.0 to 1.0
	CRGBColor(double r, double g, double b);

	friend std::ostream& operator<<(std::ostream& os, const CRGBColor& color);

	CRGBColor& operator+=(const CRGBColor& other);

public:
	int R = 255;
	int G = 255;
	int B = 255;
	
	static CRGBColor Random();

	// Basic colors
	static CRGBColor Red;
	static CRGBColor Green;
	static CRGBColor Blue;
	static CRGBColor Black;
	static CRGBColor Grey;
	static CRGBColor White;
};


