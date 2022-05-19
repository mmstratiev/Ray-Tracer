#include <fstream>

#include "Globals.h"
#include "Camera.h"
#include "Pixel.h"
#include "Vector.h"
#include "Triangle.h"

CCamera::CCamera()
{
}

void CCamera::Reset()
{
	Translation	= CVector(0, 0, 0);
	Rotation	= CMatrix3x3::Identity;
}

void CCamera::SetResolution(int width, int height)
{
	Width = width;
	Height = height;
}

void CCamera::SetBackground(const CRGBColor& background)
{
	Background = background;
}

void CCamera::SetTranslation(const CVector& translation)
{
	Translation = translation;
}

void CCamera::SetRotation(const CMatrix3x3& rotation)
{
	Rotation = rotation;
}

CCamera& CCamera::Translate(const CVector& dt)
{
	Translation += dt;
	return *this;
}

CCamera& CCamera::Translate(double dx, double dy, double dz)
{
	return this->Translate(CVector(dx, dy, dz));
}

CCamera& CCamera::Rotate(const CVector& dr)
{
	Rotation = Rotation * CMatrix3x3(dr);
	return *this;
}

CCamera& CCamera::Rotate(double dx, double dy, double dz)
{
	return this->Rotate(CVector(dx, dy, dz));
}

CCamera& CCamera::Dolly(double value)
{
	return this->Translate(WorldForward * value);
}

CCamera& CCamera::Truck(double value)
{
	return this->Translate(WorldRight * value);
}

CCamera& CCamera::Pedestal(double value)
{
	return this->Translate(WorldUp * value);
}

CCamera& CCamera::Pan(double angle)
{
	return this->Rotate(0.0f, angle, 0.0f);
}

CCamera& CCamera::Tilt(double angle)
{
	return this->Rotate(angle, 0.0f, 0.0f);
}

CCamera& CCamera::Roll(double angle)
{
	return this->Rotate(0.0f, 0.0f, angle);
}

const CVector& CCamera::GetTranslation() const
{
	return Translation;
}

const CMatrix3x3& CCamera::GetRotation() const
{
	return Rotation;
}

const CRGBColor& CCamera::GetBackround() const
{
	return Background;
}

int CCamera::GetWidth() const
{
	return Width;
}

int CCamera::GetHeight() const
{
	return Height;
}