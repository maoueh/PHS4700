#include "matrix4.h"

template<> const Matrix4<FLOAT> Matrix4<FLOAT>::ZERO(0.0f, 0.0f, 0.0f, 0.0f,
                                                     0.0f, 0.0f, 0.0f, 0.0f,
                                                     0.0f, 0.0f, 0.0f, 0.0f,
                                                     0.0f, 0.0f, 0.0f, 0.0f);
template<> const Matrix4<FLOAT> Matrix4<FLOAT>::IDENTITY(1.0f, 0.0f, 0.0f, 0.0f,
                                                         0.0f, 1.0f, 0.0f, 0.0f,
                                                         0.0f, 0.0f, 1.0f, 0.0f,
                                                         0.0f, 0.0f, 0.0f, 1.0f);

template<> const Matrix4<DOUBLE> Matrix4<DOUBLE>::ZERO(0.0, 0.0, 0.0, 0.0,
                                                       0.0, 0.0, 0.0, 0.0,
                                                       0.0, 0.0, 0.0, 0.0,
                                                       0.0, 0.0, 0.0, 0.0);
template<> const Matrix4<DOUBLE> Matrix4<DOUBLE>::IDENTITY(1.0, 0.0, 0.0, 0.0,
                                                           0.0, 1.0, 0.0, 0.0,
                                                           0.0, 0.0, 1.0, 0.0,
                                                           0.0, 0.0, 0.0, 1.0);
