#include "Ray.h"

#include "Globals.h"
#include "Utilities.h"
#include "Triangle.h"

CRay::CRay(const CVector& origin, const CVector& direction, double length)
	: Origin(origin)
	, Direction(direction)
	, Length(length)
{
}

bool CRay::Intersects(const CTriangle& triangle, SIntersectInfo& outIntersectInfo) const
{
	CVector v0v1 = triangle.GetV1() - triangle.GetV0();
	CVector v0v2 = triangle.GetV2() - triangle.GetV0();
	CVector N = v0v1.CrossProduct(v0v2);

	float area2 = N.GetLength();
	
	// check if ray and plane are parallel
	float rProj = N.DotProduct(Direction);
	if (IsDoubleNearlyZero(rProj))
	    return false;
	
	double rpDist	= CVector::DotProduct(triangle.GetV0() - Origin, N);
	double t        = rpDist / rProj;
	
	// check if the triangle is behind the ray
	if (t < 0 || IsDoubleNearlyZero(t)) return false; // the triangle is behind 
	
	// compute the intersection point P
	outIntersectInfo.HitPoint = Origin + (Direction * t);

	// if length is not infinite, check if the ray is longer than needed
	double currentLength = (outIntersectInfo.HitPoint - Origin).GetLength();
	if (!IsDoubleNearlyZero(Length) && currentLength > Length)
		return false;
	
	// edge 0
	CVector edge0 = triangle.GetV1() - triangle.GetV0();
	CVector v0p = outIntersectInfo.HitPoint - triangle.GetV0();
	CVector C1 = edge0.CrossProduct(v0p); // vector perpendicular to triangle's plane 
	if (N.DotProduct(C1) < 0) return false; // P is on the right side 
	
	// edge 1
	CVector edge1 = triangle.GetV2() - triangle.GetV1();
	CVector v1p = outIntersectInfo.HitPoint - triangle.GetV1();
	CVector C2 = edge1.CrossProduct(v1p);
	if (N.DotProduct(C2) < 0)  return false; // P is on the right side 
	
	// edge 2
	CVector edge2 = triangle.GetV0() - triangle.GetV2();
	CVector v2p = outIntersectInfo.HitPoint - triangle.GetV2();
	CVector C3 = edge2.CrossProduct(v2p);
	if (N.DotProduct(C3) < 0) return false; // P is on the right side; 
	
	outIntersectInfo.UV.X = v0p.CrossProduct(v0v2).GetLength() / v0v1.CrossProduct(v0v2).GetLength();
	outIntersectInfo.UV.Y = v0v1.CrossProduct(v0p).GetLength() / v0v1.CrossProduct(v0v2).GetLength();

	outIntersectInfo.FaceNormal = triangle.GetNormal();
	outIntersectInfo.HitNormal  = outIntersectInfo.FaceNormal;

	return true; // this ray hits the triangle
}

bool CRay::TraceAgainst(const CGeometricObject& geometricObject, SIntersectInfo& outIntersectInfo, ETraceFlags flags) const
{
	bool result = false;
	double minDistance = std::numeric_limits<double>::max();

	int trianglesCount = geometricObject.GetTriangleCount();
	int hitTriangle = 0;

	for (int triIndex = 0; triIndex < trianglesCount; triIndex++)
	{
		SIntersectInfo currIntersectInfo;
		if (this->Intersects(geometricObject.GetTriangle(triIndex), currIntersectInfo))
		{
			result = true;
			currIntersectInfo.HitObject = &geometricObject;

			if (flags & ETraceFlags::Complex)
			{
				double currDistance = (currIntersectInfo.HitPoint - Origin).GetLength();
				if (currDistance < minDistance)
				{
					hitTriangle = triIndex;
					outIntersectInfo = currIntersectInfo;
					minDistance = currDistance;
				}
			}
			else
			{
				hitTriangle = triIndex;
				outIntersectInfo = currIntersectInfo;
				break;
			}
		}
	}

	if (result && geometricObject.GetMaterial().GetSmoothShading() && (flags & ETraceFlags::SmoothHitNormal))
	{
		CVector v0n, v1n, v2n;
		geometricObject.GetTriVertNormals(hitTriangle, v0n, v1n, v2n);
		outIntersectInfo.HitNormal = v1n * outIntersectInfo.UV.X +
			                         v2n * outIntersectInfo.UV.Y +
			                         v0n * (1 - outIntersectInfo.UV.X - outIntersectInfo.UV.Y);
	}

	return result;
}

bool CRay::Trace(SIntersectInfo& outIntersectInfo, ETraceFlags flags) const
{
	bool result = false;
	double minDistance = std::numeric_limits<double>::max();

	for (const CGeometricObject& geometricObject : GeometricObjects)
	{
		SIntersectInfo currIntersectInfo;
		if (this->TraceAgainst(geometricObject, currIntersectInfo, flags))
		{
			result = true;

			if (flags & ETraceFlags::Complex)
			{
				double currDistance = (currIntersectInfo.HitPoint - Origin).GetLength();
				if (currDistance < minDistance)
				{
					outIntersectInfo = currIntersectInfo;
					minDistance = currDistance;
				}
			}
			else
			{
				outIntersectInfo = currIntersectInfo;
				break;
			}
		}
	}

	return result;
}
