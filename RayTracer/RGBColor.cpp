#include <algorithm>
#include <random>

#include "RGBColor.h"

CRGBColor CRGBColor::Red	= CRGBColor(255, 0, 0);
CRGBColor CRGBColor::Green	= CRGBColor(0, 255, 0);
CRGBColor CRGBColor::Blue	= CRGBColor(0, 0, 255);
CRGBColor CRGBColor::Black	= CRGBColor(0, 0, 0);
CRGBColor CRGBColor::Grey	= CRGBColor(128, 128, 128);
CRGBColor CRGBColor::White	= CRGBColor(255, 255, 255);

CRGBColor::CRGBColor()
{
}

CRGBColor::CRGBColor(int r, int g, int b)
	: R(r)
	, G(g)
	, B(b)
{
	R = std::clamp(r, 0, 255);
	G = std::clamp(g, 0, 255);
	B = std::clamp(b, 0, 255);
}

CRGBColor::CRGBColor(double r, double g, double b)
	: R(255 * r)
	, B(255 * g)
	, G(255 * b)
{}

CRGBColor& CRGBColor::operator+=(const CRGBColor& other)
{
	R = std::clamp(R + other.R, 0, 255);
	G = std::clamp(G + other.G, 0, 255);
	B = std::clamp(B + other.B, 0, 255);

	return *this;
}

CRGBColor CRGBColor::Random()
{
	std::random_device	dev;
	std::mt19937		range(dev());
	std::uniform_int_distribution<std::mt19937::result_type> distribution(0, 255);

	return CRGBColor((int)distribution(range), (int)distribution(range), (int)distribution(range));
}

std::ostream& operator<<(std::ostream& os, const CRGBColor& color)
{
	return os << color.R << " " << color.G << " " << color.B << "\t";
}