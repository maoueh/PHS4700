#include "quaternion.h"

template<> const Quaternion<float>  Quaternion<float>::IDENTITY(1.0f, 0.0f, 0.0f, 0.0f);
template<> const Quaternion<float>  Quaternion<float>::ZERO(0.0f, 0.0f, 0.0f, 0.0f);

template<> const Quaternion<double> Quaternion<double>::IDENTITY(1.0, 0.0, 0.0, 0.0);
template<> const Quaternion<double> Quaternion<double>::ZERO(0.0, 0.0, 0.0, 0.0);
