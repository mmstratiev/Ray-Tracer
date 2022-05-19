#pragma once
#include <unordered_set>
#include <unordered_map>

#include "Material.h"
#include "Triangle.h"

class CGeometricObject
{
public:
	CGeometricObject(const CMaterial& material);

	void AddVertex(const CVector& Vertex, int index);
	void AddTriangle(int V0Index, int V1Index, int V2Index);

	const CMaterial& GetMaterial() const;

	int GetTriangleCount() const;
	CTriangle GetTriangle(int triangleIndex) const;
	void GetTriVertNormals(int triangleIndex, CVector& outV0n, CVector& outV1n, CVector& outV2n) const;

private:
	struct SVertex
	{
		CVector                  Position;
		std::unordered_set<int>  ConnectedTrianglesIDs;
	};

	struct STriangle
	{
		int VerticesIDs[3];

		STriangle(int V0Index, int V1Index, int V2Index)
			: VerticesIDs{ V0Index, V1Index, V2Index }
		{}
	};

private:
	const CMaterial			Material;
	std::vector<STriangle>  Triangles;
	std::unordered_map<int, SVertex> Vertices;

	mutable std::unordered_map<int, CVector> VertToVertNormals;
};

