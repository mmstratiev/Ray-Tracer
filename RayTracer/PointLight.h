#pragma once
#include "Vector.h"

struct SShadingInfo
{
	CVector LightDir;
	double	SphereRadius	= 0.0f;
	double	Intensity		= 0.0f;
};

class CPointLight
{
public:
	CPointLight();
	CPointLight(CVector translation, int intensity);

	const CVector&	GetTranslation() const;
	int				GetIntensity() const;

	SShadingInfo	GetShadingInfoAtPoint(const CVector& orig) const;

private:
	CVector Translation;
	int		Intensity	= 0;
};

