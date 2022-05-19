#include "Material.h"

CMaterial::CMaterial(EType type, const CVector& albedo, bool smoothShade)
	: Albedo(albedo)
	, Type(type)
	, SmoothShading(smoothShade)
{
}

CMaterial::CMaterial(std::string type, const CVector& albedo, bool smoothShade)
	: CMaterial(CMaterial::ParseType(type), albedo, smoothShade)
{
}

const CVector& CMaterial::GetAlbedo() const
{
	return Albedo;
}

CMaterial::EType CMaterial::GetType() const
{
	return Type;
}

bool CMaterial::GetSmoothShading() const
{
	return SmoothShading;
}

CMaterial::EType CMaterial::ParseType(std::string type)
{
	EType result = EType::Diffuse;
	if (type == "reflective" || type == "Reflective")
	{
		result = EType::Reflective;
	}
	return result;
}
