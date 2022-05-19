#include "Globals.h"

const double kPI				= std::acos(-1);
const double kDegreesToRadians	= kPI / 180.0f;
const double kRadiansToDegrees	= 180.0f / kPI;

const CVector WorldForward(0.0f, 0.0f, -1.0f);
const CVector WorldUp(0.0f, 1.0f, 0.0f);
const CVector WorldRight(1.0f, 0.0f, 0.0f);

std::vector<CGeometricObject> GeometricObjects;
std::vector<CPointLight>      Lights;
std::vector<CMaterial>        Materials;
