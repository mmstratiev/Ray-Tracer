#include "PointLight.h"
#include "Globals.h"

CPointLight::CPointLight()
{
}

CPointLight::CPointLight(CVector translation, int intensity)
	: Translation(translation)
	, Intensity(intensity)
{}

const CVector& CPointLight::GetTranslation() const
{
	return Translation;
}

int CPointLight::GetIntensity() const
{
	return Intensity;
}

SShadingInfo CPointLight::GetShadingInfoAtPoint(const CVector& orig) const
{
	SShadingInfo result;
	result.LightDir		= Translation - orig;
	result.SphereRadius = result.LightDir.GetLength();
	result.LightDir.Normalize();

	result.LightDir.X /= result.SphereRadius;
	result.LightDir.Y /= result.SphereRadius;
	result.LightDir.Z /= result.SphereRadius;

	double sphereArea = 4.0f * kPI * result.SphereRadius * result.SphereRadius;
	result.Intensity = (double) Intensity / sphereArea;

	return result;
}
