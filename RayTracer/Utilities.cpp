#include "Utilities.h"

#include <cstdlib>

bool IsDoubleNearlyZero(double inDouble)
{
	return std::abs(inDouble) < kEpsilon;
}
