#ifndef VECTOR4_H
#define VECTOR4_H

#include "common.h"

template <class Real>
class Vector4
{
public:
    static const Vector4 ZERO;
    static const Vector4 UNIT_X;
    static const Vector4 UNIT_Y;
    static const Vector4 UNIT_Z;
    static const Vector4 UNIT_W;

    inline Vector4();
    inline Vector4(Real x, Real y, Real z, Real w = 1.0f);
    inline explicit Vector4(Real* coordinates); // Takes a four element <Real> array
    inline explicit Vector4(Real scalar, Real w = 1.0f);
    inline Vector4(const Vector4& other);

    inline Real  x() const;
    inline Real& x();
    inline Real  y() const;
    inline Real& y();
    inline Real  z() const;
    inline Real& z();
    inline Real  w() const;
    inline Real& w();

    inline void set(Real scalar, Real w = 1.0f);
    inline void set(Real x, Real y, Real z);
    inline void set(Real x, Real y, Real z, Real w);
    inline void set(Real* coordinates);  // Takes a four element <Real> array
    inline void set2(Real* coordinates); // Takes a two element <Real> array
    inline void set3(Real* coordinates); // Takes a three element <Real> array

    inline Vector4& operator=  (const Vector4& rightSide);   

    inline operator const Real* () const;
    inline operator Real* ();
    inline Real  operator[] (INT index) const;
    inline Real& operator[] (INT index);
    
    inline BOOL     operator== (const Vector4& rightSide) const;
    inline BOOL     operator!= (const Vector4& rightSide) const;

    inline Vector4& operator+= (const Vector4& rightSide);
    inline Vector4& operator-= (const Vector4& rightSide);
    inline Vector4& operator*= (Real scalar);
    inline Vector4& operator/= (Real scalar);

    inline Vector4 operator- () const;
    inline Vector4 operator+ (const Vector4& rightSide) const;
    inline Vector4 operator- (const Vector4& rightSide) const;
    inline Vector4 operator* (Real scalar) const;
    inline Vector4 operator/ (Real scalar) const;

    // Be careful : the length is not squarred, use magnitude for the squarred value
    inline Real    length();
    inline Real    magnitude();
    inline Vector4 normalize();

    inline static Real    scalarProduct(Vector4& leftSide, const Vector4& rightSide); // Same as dotProduct
    inline static Real    dotProduct(Vector4& leftSide, const Vector4& rightSide);    // Same as scalarProduct

    inline static Vector4 vectorProduct(Vector4& leftSide, const Vector4& rightSide); // Same as crossProduct
    inline static Vector4 crossProduct(Vector4& leftSide, const Vector4& rightSide);  // Same as vectorProduct
    inline static Real    distance(Vector4& leftSide, const Vector4& rightSide);

    Real components[4];
};

template <class Real>
Vector4<Real> operator* (Real scalar, const Vector4<Real>& rightSide);

template <class Real>
Vector4<Real> operator/ (Real scalar, const Vector4<Real>& rightSide);

template <class Real>
ostream& operator<< (ostream& outputStream, const Vector4<Real>& vector);

#include "vector4.inl"

typedef Vector4<FLOAT>  Vector4f;
typedef Vector4<DOUBLE> Vector4d;
typedef Vector4<FLOAT>  Vector;

#endif
