#pragma once
#include "Vector2D.h"
#include "Vector.h"
#include "CGeometricObject.h"

enum ETraceFlags
{
	None            = 0,
	Complex	        = 1 << 0, // complex trace will return only the closest hit. Non-complex will return the first hit.
	SmoothHitNormal = 1 << 1, // more expensive
};

inline ETraceFlags operator|(ETraceFlags a, ETraceFlags b)
{
	return static_cast<ETraceFlags>(static_cast<int>(a) | static_cast<int>(b));
}

struct SIntersectInfo
{
	const CGeometricObject* HitObject = nullptr;
	CVector		            FaceNormal;
	CVector		            HitNormal;
	CVector		            HitPoint;
	CVector2D	            UV;
};

class CRay
{
public:
	CRay(const CVector& origin, const CVector& direction, double length = 0.0f);

	bool Intersects(const CTriangle& triangle, SIntersectInfo& outIntersectInfo) const;

	bool TraceAgainst(const CGeometricObject& geometricObject, SIntersectInfo& outIntersectInfo, ETraceFlags flags = ETraceFlags::None) const;
	bool Trace(SIntersectInfo& outIntersectInfo, ETraceFlags flags = ETraceFlags::None) const;

	CVector	Origin;
	CVector	Direction;
	double	Length = 0.0f; // infinite by default
};

