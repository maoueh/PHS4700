#ifndef GAME_ENGINE_MATH_UTILS_H
#define GAME_ENGINE_MATH_UTILS_H

#include "common.h"
#include "vector3.h"
#include "vector4.h"

template <class Real>
class MathUtils
{
public:
    static Vector3<Real> interpolate3(const Vector3<Real>& v1, const Vector3<Real>& v2, 
                                      Real valueLookedFor, INT deltaComponent);
    static Vector4<Real> interpolate4(const Vector4<Real>& v1, const Vector4<Real>& v2, 
                                      Real valueLookedFor, INT deltaComponent);

private:
    // Class cannot be instantiated
    MathUtils();
    MathUtils(const MathUtils& other);
    MathUtils& operator=(const MathUtils& rightSide);
};

#include "math_utils.inl"

#endif