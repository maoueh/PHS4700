#ifndef QUATERNION_H
#define QUATERNION_H

#include "common.h"
#include "matrix3.h"
#include "vector3.h"
#include "vector4.h"

template <class Real>
class Quaternion
{
public:
    // Constants
    static const Quaternion IDENTITY;
    static const Quaternion ZERO;

    // A quaternion is q = w + x*i + y*j + z*k
    Quaternion();  // uninitialized
    Quaternion(Real w, Real x, Real y, Real z);
    // q(cos(angle/2), sin(angle/2) * axis vector) (the vector will be normalized)
    Quaternion(Real angle, const Vector3<Real>& axis);
    Quaternion(Real angle, const Vector4<Real>& axis);
    // w = values[0], x = values[1], y = values[2] and z = values[3]
    Quaternion(Real* values); 
    Quaternion(const Quaternion& other);

    // Member access  0 = w, 1 = x, 2 = y, 3 = z
    operator const Real*() const;
    operator Real*();
    Real  operator[] (int i) const;
    Real& operator[] (int i);
    Real  w() const;
    Real& w();
    Real  x() const;
    Real& x();
    Real  y() const;
    Real& y();
    Real  z() const;
    Real& z();

    // Assign array values : values[0] = w, values[1] = x, values[2] = y and values[3] = z
    void assignTo(Real* values);
    // Set quaternion components : w = values[0], x = values[1], y = values[2] and z = values[3]
    void set(Real* values);
    void set(Real w, Real x, Real y, Real z);

    Quaternion& operator= (const Quaternion& other);

    bool operator== (const Quaternion& rightSide) const;
    bool operator!= (const Quaternion& rightSide) const;
    bool operator<  (const Quaternion& rightSide) const;
    bool operator<= (const Quaternion& rightSide) const;
    bool operator>  (const Quaternion& rightSide) const;
    bool operator>= (const Quaternion& rightSide) const;

    Quaternion operator+ (const Quaternion& rightSide) const;
    Quaternion operator- (const Quaternion& rightSide) const;
    // NOTE:  Multiplication is not usualy commutative, so in most cases p * q != q * p
    Quaternion operator* (const Quaternion& rightSide) const;
    Quaternion operator* (Real scalar) const;
    Quaternion operator/ (Real scalar) const;
    Quaternion operator- () const;

    Quaternion& operator+= (const Quaternion& rightSide);
    Quaternion& operator-= (const Quaternion& rightSide);
    Quaternion& operator*= (Real scalar);
    Quaternion& operator/= (Real scalar);

    // functions of a quaternion
    Real length() const;                          // Length of 4 components
    Real magnitude() const;                       // Squared length of 4 components
    Real dot(const Quaternion& rightSide) const;  // Dot product of two quaternion
    Real normalize();                             // Make the 4 components unit length
    Quaternion inverse() const;                   // Apply to non-zero quaternion
    Quaternion conjugate() const;                 // Returns the conjugate of the quaternion

    void fromAxisAngle(Real angle, const Vector3<Real>& axis); // Assign the quaternion rotation with an axis vector and an angle
    void fromAxisAngle(Real angle, const Vector4<Real>& axis);

    void toRotationMatrix(Matrix3<Real>& matrix)  const;       // Transform quaternion to a rotation matrix
    void toAxisAngle(Real& angle, Vector3<Real>& axis) const;  // Transform quaternion to an axis vector and an angle
    void toAxisAngle(Real& angle, Vector4<Real>& axis) const;

    Real components[4];

private:
    int compareArrays(const Quaternion& rightSide) const;

};

template <class Real>
Quaternion<Real> operator* (Real scalar, const Quaternion<Real>& rightSide);

template <class Real>
ostream& operator<< (ostream& outputStream, const Quaternion<Real>& quaternion);

#include "quaternion.inl"

typedef Quaternion<float> Quaternionf;
typedef Quaternion<double> Quaterniond;

#endif
