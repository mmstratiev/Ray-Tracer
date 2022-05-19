#include "CGeometricObject.h"

CGeometricObject::CGeometricObject(const CMaterial& material)
	: Material(material)
{
}

void CGeometricObject::AddVertex(const CVector& Vertex, int index)
{
	SVertex& it = Vertices[index];
	it.Position = Vertex;
}

void CGeometricObject::AddTriangle(int V0Index, int V1Index, int V2Index)
{
	Triangles.push_back({ V0Index, V1Index, V2Index });

	int triangleindex = Triangles.size() - 1;
	Vertices[V0Index].ConnectedTrianglesIDs.insert(triangleindex);
	Vertices[V1Index].ConnectedTrianglesIDs.insert(triangleindex);
	Vertices[V2Index].ConnectedTrianglesIDs.insert(triangleindex);
}

const CMaterial& CGeometricObject::GetMaterial() const
{
	return Material;
}

int CGeometricObject::GetTriangleCount() const
{
	return Triangles.size();
}

CTriangle CGeometricObject::GetTriangle(int triangleIndex) const
{
	const STriangle& triangle = Triangles[triangleIndex];
	const SVertex& V0 = Vertices.at(triangle.VerticesIDs[0]);
	const SVertex& V1 = Vertices.at(triangle.VerticesIDs[1]);
	const SVertex& V2 = Vertices.at(triangle.VerticesIDs[2]);

	return CTriangle(V0.Position, V1.Position, V2.Position);
}

void CGeometricObject::GetTriVertNormals(int triangleIndex, CVector& outV0n, CVector& outV1n, CVector& outV2n) const
{
	const STriangle& triangle = Triangles[triangleIndex];

	auto getOrGenerateNormal = [&](int vertIndex) -> CVector
	{
		CVector resultNormal;
		auto vertNormalIt = VertToVertNormals.find(vertIndex);
		if (vertNormalIt != VertToVertNormals.end())
		{
			// Already has generated normal, return
			resultNormal = vertNormalIt->second;
		}
		else
		{
			// Generate and cache normal
			const SVertex& vertex = Vertices.at(vertIndex);

			for (auto currTriIndex : vertex.ConnectedTrianglesIDs)
			{
				const STriangle& currTriangle = Triangles[currTriIndex];
				const SVertex& currV0 = Vertices.at(currTriangle.VerticesIDs[0]);
				const SVertex& currV1 = Vertices.at(currTriangle.VerticesIDs[1]);
				const SVertex& currV2 = Vertices.at(currTriangle.VerticesIDs[2]);
				resultNormal += CTriangle(currV0.Position, currV1.Position, currV2.Position).GetNormal();
			}

			resultNormal.Normalize();
			VertToVertNormals[vertIndex] = resultNormal;
		}
		return resultNormal;
	};

	outV0n = getOrGenerateNormal(triangle.VerticesIDs[0]);
	outV1n = getOrGenerateNormal(triangle.VerticesIDs[1]);
	outV2n = getOrGenerateNormal(triangle.VerticesIDs[2]);
}
