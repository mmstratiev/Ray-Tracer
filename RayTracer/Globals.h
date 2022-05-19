#pragma once
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "CGeometricObject.h"
#include "PointLight.h"
#include "Material.h"

extern const double kPI;
extern const double kDegreesToRadians;
extern const double kRadiansToDegrees;

extern const CVector WorldForward;
extern const CVector WorldUp;
extern const CVector WorldRight;

// There are plenty of smarter ways to do this than a global variable, but for the scope of this project this will do for now.
extern std::vector<CGeometricObject> GeometricObjects;
extern std::vector<CPointLight>	     Lights;
extern std::vector<CMaterial>	     Materials;
