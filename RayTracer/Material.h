#pragma once
#include "Vector.h"

class CMaterial
{
public:
	enum class EType 
	{
		Diffuse,
		Reflective
	};

	CMaterial(EType type, const CVector& albedo, bool smoothShade = false);
	CMaterial(std::string type, const CVector& albedo, bool smoothShade = false);

	const CVector& GetAlbedo() const;
	EType          GetType() const;
	bool           GetSmoothShading() const;


	static EType ParseType(std::string type);

private:
	CVector Albedo        = CVector(1.0f, 1.0f, 1.0f);
	EType	Type          = EType::Diffuse;
	bool	SmoothShading = false;
};

