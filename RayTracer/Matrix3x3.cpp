#include "Matrix3x3.h"
#include "Globals.h"

CMatrix3x3 CMatrix3x3::Identity = CMatrix3x3();

CMatrix3x3::CMatrix3x3()
{
}

CMatrix3x3::CMatrix3x3(const CVector& angles)
{
    this->SetFromEuler(angles);
}

CMatrix3x3::CMatrix3x3(double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33)
{
    Matrix[0][0] = a11;  Matrix[0][1] = a12; Matrix[0][2] = a13;
    Matrix[1][0] = a21;  Matrix[1][1] = a22; Matrix[1][2] = a23;
    Matrix[2][0] = a31;  Matrix[2][1] = a32; Matrix[2][2] = a33;
}

void CMatrix3x3::SetFromEuler(CVector angles)
{
    CVector radians = angles * kDegreesToRadians;

    // Calculate rotation about x axis
    CMatrix3x3 R_x = CMatrix3x3(  1, 0, 0,
                            0, cos(radians.X), -sin(radians.X),
                            0, sin(radians.X), cos(radians.X));

    // Calculate rotation about y axis
    CMatrix3x3 R_y = CMatrix3x3(  std::cos(radians.Y), 0, sin(radians.Y),
                            0, 1, 0,
                            -sin(radians.Y), 0, cos(radians.Y));

    // Calculate rotation about z axis
    CMatrix3x3 R_z = CMatrix3x3(  cos(radians.Z), -sin(radians.Z), 0,
                            sin(radians.Z), cos(radians.Z), 0,
                            0, 0, 1);

    // Combined rotation matrix
    *this = R_z * R_y * R_x;
}

CMatrix3x3 CMatrix3x3::operator*(const CMatrix3x3& other) const
{
    CMatrix3x3 result;
    for (int i = 0; i < 3; ++i) {

        for (int j = 0; j < 3; ++j) {

            double sum = 0;
            for (int k = 0; k < 3; ++k) {
                sum += Matrix[i][k] * other.Matrix[k][j];
            }
            result.Matrix[i][j] = sum;
        }
    }
    return result;
}

CVector CMatrix3x3::operator*(const CVector& other) const
{
    CVector result;
    result.X = Matrix[0][0] * other.X + Matrix[0][1] * other.Y + Matrix[0][2] * other.Z;
    result.Y = Matrix[1][0] * other.X + Matrix[1][1] * other.Y + Matrix[1][2] * other.Z;
    result.Z = Matrix[2][0] * other.X + Matrix[2][1] * other.Y + Matrix[2][2] * other.Z;
    return result;
}
