#ifndef VECTOR3_H
#define VECTOR3_H

#include "common.h"

template <class Real>
class Vector3
{

public:
    static const Vector3 ZERO;
    static const Vector3 UNIT_X;
    static const Vector3 UNIT_Y;
    static const Vector3 UNIT_Z;

    inline Vector3();
    inline Vector3(Real x, Real y, Real z);
    inline explicit Vector3(Real* coordinates); // Takes a three element <Real> array
    inline explicit Vector3(Real scalar);
    inline Vector3(const Vector3& other);

    inline Real  x() const;
    inline Real& x();
    inline Real  y() const;
    inline Real& y();
    inline Real  z() const;
    inline Real& z();

    inline void set(Real scalar);
    inline void set(Real x, Real y, Real z);
    inline void set(Real* coordinates);  // Takes a three element <Real> array
    inline void set2(Real* coordinates); // Takes a two element <Real> array

    inline void assignTo(Real* values); // Assign the array received with the components of the vector

    inline Vector3& operator=  (const Vector3& rightSide);   

    inline operator const Real* () const;
    inline operator Real* ();
    inline Real  operator[] (INT index) const;
    inline Real& operator[] (INT index);
    
    inline BOOL     operator== (const Vector3& rightSide) const;
    inline BOOL     operator!= (const Vector3& rightSide) const;

    inline Vector3& operator+= (const Vector3& rightSide);
    inline Vector3& operator-= (const Vector3& rightSide);
    inline Vector3& operator*= (Real scalar);
    inline Vector3& operator/= (Real scalar);

    inline Vector3 operator- () const;
    inline Vector3 operator+ (const Vector3& rightSide) const;
    inline Vector3 operator- (const Vector3& rightSide) const;
    inline Vector3 operator* (Real scalar) const;
    inline Vector3 operator/ (Real scalar) const;

    // Be careful : the length is not squarred, use magnitude for the squarred value
    inline Real    length() const;
    inline Real    magnitude() const;
    inline Vector3 normalize() const;

    inline static Real    scalarProduct(Vector3& leftSide, const Vector3& rightSide); // Same as dotProduct
    inline static Real    dotProduct(Vector3& leftSide, const Vector3& rightSide);    // Same as scalarProduct

    inline static Vector3 vectorProduct(Vector3& leftSide, const Vector3& rightSide); // Same as crossProduct
    inline static Vector3 crossProduct(Vector3& leftSide, const Vector3& rightSide);  // Same as vectorProduct
    inline static Real    distance(Vector3& leftSide, const Vector3& rightSide);

    Real components[3];
};

template <class Real>
Vector3<Real> operator* (Real scalar, const Vector3<Real>& rightSide);

template <class Real>
Vector3<Real> operator/ (Real scalar, const Vector3<Real>& rightSide);

template <class Real>
ostream& operator<< (ostream& outputStream, const Vector3<Real>& vector);

#include "vector3.inl"

typedef Vector3<FLOAT>  Vector3f;
typedef Vector3<DOUBLE> Vector3d;

#endif
