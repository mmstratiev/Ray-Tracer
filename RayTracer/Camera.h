#pragma once
#include "Vector.h"
#include "Matrix3x3.h"
#include "RGBColor.h"

class CCamera
{
public:
	CCamera();
	void Reset();

	void SetResolution(int width, int height);
	void SetBackground(const CRGBColor& background);
	void SetTranslation(const CVector& translation);
	void SetRotation(const CMatrix3x3& rotation);

	CCamera& Translate(const CVector& dt);
	CCamera& Translate(double dx, double dy, double dz);
	CCamera& Rotate(const CVector& dr);
	CCamera& Rotate(double dx, double dy, double dz);

	// Helper methods
	CCamera& Dolly(double value);
	CCamera& Truck(double value);
	CCamera& Pedestal(double value);
	CCamera& Pan(double angle);
	CCamera& Tilt(double angle);
	CCamera& Roll(double angle);

	const CVector&		GetTranslation() const;
	const CMatrix3x3&	GetRotation() const;
	const CRGBColor&	GetBackround() const;

	int GetWidth() const;
	int GetHeight() const;

private:
	int			Width		= 800;
	int			Height		= 600;
	CRGBColor	Background;

	CVector		Translation = CVector(0, 0, 0);
	CMatrix3x3	Rotation	= CMatrix3x3::Identity;
};

