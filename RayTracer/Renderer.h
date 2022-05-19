#pragma once
#include "Camera.h"
#include "Ray.h"
#include "RGBColor.h"

class CRenderer
{
public:
	CRenderer(const CCamera& camera);

	void Render(const std::string& outputFile);

	// TODO: Enum flags
	void SetBarycentricRender(bool value);
	void SetLit(bool value);

private:
	CRGBColor RayTrace(const CRay& ray, int depth = 0) const;
	CVector Reflect(const CVector& in, const CVector& inNormal) const;

private:
	const CCamera& Camera;
	bool Barycentric = false;
	bool Lit		 = false;
};

