#include "vector4.h"

template<> const Vector4<FLOAT> Vector4<FLOAT>::ZERO(0.0f, 0.0f, 0.0f, 0.0f);

template<> const Vector4<FLOAT> Vector4<FLOAT>::UNIT_X(1.0f, 0.0f, 0.0f, 0.0f);
template<> const Vector4<FLOAT> Vector4<FLOAT>::UNIT_Y(0.0f, 1.0f, 0.0f, 0.0f);
template<> const Vector4<FLOAT> Vector4<FLOAT>::UNIT_Z(0.0f, 0.0f, 1.0f, 0.0f);
template<> const Vector4<FLOAT> Vector4<FLOAT>::UNIT_W(0.0f, 0.0f, 0.0f, 1.0f);

template<> const Vector4<DOUBLE> Vector4<DOUBLE>::ZERO(0.0, 0.0, 0.0, 0.0);

template<> const Vector4<DOUBLE> Vector4<DOUBLE>::UNIT_X(1.0, 0.0, 0.0, 0.0);
template<> const Vector4<DOUBLE> Vector4<DOUBLE>::UNIT_Y(0.0, 1.0, 0.0, 0.0);
template<> const Vector4<DOUBLE> Vector4<DOUBLE>::UNIT_Z(0.0, 0.0, 1.0, 0.0);
template<> const Vector4<DOUBLE> Vector4<DOUBLE>::UNIT_W(0.0, 0.0, 0.0, 1.0);