#include "vector3.h"

template<> const Vector3<FLOAT> Vector3<FLOAT>::ZERO(0.0f, 0.0f, 0.0f);

template<> const Vector3<FLOAT> Vector3<FLOAT>::UNIT_X(1.0f, 0.0f, 0.0f);
template<> const Vector3<FLOAT> Vector3<FLOAT>::UNIT_Y(0.0f, 1.0f, 0.0f);
template<> const Vector3<FLOAT> Vector3<FLOAT>::UNIT_Z(0.0f, 0.0f, 1.0f);

template<> const Vector3<DOUBLE> Vector3<DOUBLE>::ZERO(0.0, 0.0, 0.0);

template<> const Vector3<DOUBLE> Vector3<DOUBLE>::UNIT_X(1.0, 0.0, 0.0);
template<> const Vector3<DOUBLE> Vector3<DOUBLE>::UNIT_Y(0.0, 1.0, 0.0);
template<> const Vector3<DOUBLE> Vector3<DOUBLE>::UNIT_Z(0.0, 0.0, 1.0);