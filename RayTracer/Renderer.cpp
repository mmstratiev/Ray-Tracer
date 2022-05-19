#include "Renderer.h"

#include <fstream>

#include "Globals.h"
#include "RGBColor.h"
#include "Pixel.h"
#include "Ray.h"

const int     kMaxColorComponent = 255;
const int     kMaxTraceDepth	 = 5;
const double  kShadowBias        = 0.1f;
const CVector kBarycentircColors[3] = { {0.6, 0.4, 0.1}, {0.1, 0.5, 0.3}, {0.1, 0.3, 0.7} };

CRenderer::CRenderer(const CCamera& camera)
	: Camera(camera)
{
}

void CRenderer::Render(const std::string& outputFile)
{
	int width = Camera.GetWidth();
	int height = Camera.GetHeight();

	const CVector&		cameraPos = Camera.GetTranslation();
	const CMatrix3x3&	cameraRot = Camera.GetRotation();

	std::ofstream ppmFileStream(outputFile, std::ios::out | std::ios::binary);
	ppmFileStream << "P3\n";
	ppmFileStream << width << " " << height << "\n";
	ppmFileStream << kMaxColorComponent << "\n";

	double aspectRatio = (double)width / (double)height;
	for (int rowIdx = 0; rowIdx < height; ++rowIdx)
	{
		for (int colIdx = 0; colIdx < width; ++colIdx)
		{
			CPixel		pixel(colIdx, rowIdx);
			CVector2D	center = pixel.GetCenter();
			CVector2D	NdcSpace = center / CVector2D(width, height);
			CVector2D	screenSpace((2.0f * NdcSpace.X) - 1.0f, 1.0f - (2.0f * NdcSpace.Y));

			CVector	rayDir(screenSpace.X * aspectRatio, screenSpace.Y, -1.0f);
			rayDir.Normalize();
			rayDir = cameraRot * rayDir;

			CRay cameraRay(cameraPos, rayDir, 0);
			CRGBColor color = this->RayTrace(cameraRay);

			ppmFileStream << color;
		}
		ppmFileStream << "\n";
	}

	ppmFileStream.close();
}

void CRenderer::SetBarycentricRender(bool value)
{
	Barycentric = value;
}

void CRenderer::SetLit(bool value)
{
	Lit = value;
}

CRGBColor CRenderer::RayTrace(const CRay& ray, int depth) const
{
	CRGBColor result = Camera.GetBackround();
	if (depth > kMaxTraceDepth)
		return result;
	
	ETraceFlags traceFlags = ETraceFlags::Complex | ETraceFlags::SmoothHitNormal;

	SIntersectInfo hitInfo;
	if (ray.Trace(hitInfo, traceFlags))
	{
		CMaterial::EType materialType = hitInfo.HitObject->GetMaterial().GetType();
		result = CRGBColor::Black;

		if (materialType == CMaterial::EType::Reflective)
		{
			CVector reflectedOrig = hitInfo.HitPoint + hitInfo.FaceNormal * kShadowBias;
			CVector reflectedDir = this->Reflect(ray.Direction, hitInfo.HitNormal);
			CRay reflectedRay(reflectedOrig, reflectedDir);

			result = this->RayTrace(reflectedRay);

			// diminish color a bit
			result.R *= 0.8f;
			result.G *= 0.8f;
			result.B *= 0.8f;
		}
		else
		{
			CVector albedo = hitInfo.HitObject->GetMaterial().GetAlbedo();
			if (Barycentric)
			{
				albedo = kBarycentircColors[0] * hitInfo.UV.X + kBarycentircColors[1] * hitInfo.UV.Y + kBarycentircColors[2] * (1 - hitInfo.UV.X - hitInfo.UV.Y);
			}

			if (Lit || Lights.empty())
			{
				result = CRGBColor(albedo.X, albedo.Y, albedo.Z);
			}
			else 
			{
				for (const CPointLight& light : Lights)
				{
					SShadingInfo shading = light.GetShadingInfoAtPoint(hitInfo.HitPoint);

					CRay shadowRay(hitInfo.HitPoint + hitInfo.FaceNormal * kShadowBias, shading.LightDir, shading.SphereRadius);

					SIntersectInfo shadowHitInfo;
					if (!shadowRay.Trace(shadowHitInfo))
					{
						double	cosLaw = std::max<double>(0.0f, hitInfo.HitNormal.DotProduct(shading.LightDir));

						CVector colorAsVector = albedo * shading.Intensity * cosLaw;
						result += CRGBColor(colorAsVector.X, colorAsVector.Y, colorAsVector.Z);
					}
				}
			}
		}
	}
	return result;
}

CVector CRenderer::Reflect(const CVector& in, const CVector& inNormal) const
{
	CVector result = in - inNormal * in.DotProduct(inNormal) * 2.0f;
	return result;
}
