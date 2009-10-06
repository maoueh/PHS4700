#ifndef MATRIX3_H
#define MATRIX3_H

// Matrix operations are applied on the left.  For example, given a matrix M
// and a vector V, matrix-times-vector is M*V.  That is, V is treated as a
// column vector.  Some graphics APIs use V*M where V is treated as a row
// vector.  In this context the "M" matrix is really a transpose of the M as
// represented in Wild Magic.  Similarly, to apply two matrix operations M0
// and M1, in that order, you compute M1*M0 so that the transform of a vector
// is (M1*M0)*V = M1*(M0*V).  Some graphics APIs use M0*M1, but again these
// matrices are the transpose of those as represented in Wild Magic.  You
// must therefore be careful about how you interface the transformation code
// with graphics APIS.
//
// For memory organization it might seem natural to chose Real[N][N] for the
// matrix storage, but this can be a problem on a platform/console that
// chooses to store the data in column-major rather than row-major format.
// To avoid potential portability problems, the matrix is stored as Real[N*N]
// and organized in row-major order.  That is, the entry of the matrix in row
// r (0 <= r < N) and column c (0 <= c < N) is stored at index i = c+N*r
// (0 <= i < N*N).

// The (x,y,z) coordinate system is assumed to be right-handed.  Coordinate
// axis rotation matrices are of the form
//   RX =    1       0       0
//           0     cos(t) -sin(t)
//           0     sin(t)  cos(t)
// where t > 0 indicates a counterclockwise rotation in the yz-plane
//   RY =  cos(t)    0     sin(t)
//           0       1       0
//        -sin(t)    0     cos(t)
// where t > 0 indicates a counterclockwise rotation in the zx-plane
//   RZ =  cos(t) -sin(t)    0
//         sin(t)  cos(t)    0
//           0       0       1
// where t > 0 indicates a counterclockwise rotation in the xy-plane.

#include "common.h"
#include "vector3.h"

template <class Real>
class Matrix3
{
public:
    static const Matrix3 ZERO;
    static const Matrix3 IDENTITY;
    
    // If createIdentity is true, create the identity matrix. Otherwise, create the zero matrix.
    Matrix3(BOOL createIdentity = false);
    Matrix3(const Matrix3& rightSide);

    // Input read in row-major order
    Matrix3(Real a00, Real a01, Real a02,
            Real a10, Real a11, Real a12,
            Real a20, Real a21, Real a22);

    // Create a matrix from an array of numbers. The input array is
    // INTerpreted based on the isRowMajor input as
    //   true:  entry[0..15]={a00,a01,a02,a03,a10,a11,a12,a13,a20,a21,a22,
    //                        a23,a30,a31,a32,a33} [row major order]
    //   false: entry[0..15]={a00,a10,a20,a30,a01,a11,a21,a31,a02,a12,a22,
    //                        a32,a03,a13,a23,a33} [column major order]
    Matrix3(const Real values[9], BOOL isRowMajor);

    Matrix3(const Vector3<Real>& axis, Real angle);

    // Diagonal matrix
    Matrix3(Real a00, Real a11, Real a22);

    void makeZero();
    void makeIdentity();
    Matrix3& makeDiagonal(Real a00, Real a11, Real a22);
    Matrix3& fromAxisAngle(const Vector3<Real>& axis, Real angle);

    operator const Real*() const;
    operator Real*();
    const Real* operator[] (INT row) const;
    Real* operator[] (INT row);
    Real  operator() (INT row, INT column) const;
    Real& operator() (INT row, INT column);

    Vector3<Real> getRow(INT row) const;
    Vector3<Real> getColumn(INT column) const;

    void setRow(INT row, const Vector3<Real>& rightSide);
    void setColumn(INT column, const Vector3<Real>& rightSide);
    
    void getColumnMajor(Real* columnMajor) const;

    Matrix3& operator= (const Matrix3& rightSide);

    BOOL operator== (const Matrix3& rightSide) const;
    BOOL operator!= (const Matrix3& rightSide) const;
    BOOL operator<  (const Matrix3& rightSide) const;
    BOOL operator<= (const Matrix3& rightSide) const;
    BOOL operator>  (const Matrix3& rightSide) const;
    BOOL operator>= (const Matrix3& rightSide) const;

    Matrix3 operator+ (const Matrix3& rightSide) const;
    Matrix3 operator- (const Matrix3& rightSide) const;
    Matrix3 operator* (const Matrix3& rightSide) const;
    Matrix3 operator* (Real scalar) const;
    Matrix3 operator/ (Real scalar) const;
    Matrix3 operator- () const;

    Matrix3& operator+= (const Matrix3& rightSide);
    Matrix3& operator-= (const Matrix3& rightSide);
    Matrix3& operator*= (Real scalar);
    Matrix3& operator/= (Real scalar);

    Vector3<Real> operator* (const Vector3<Real>& vector) const;  // M * v

    Matrix3 transpose() const;
    Matrix3 inverse() const;
    Matrix3 adjoint() const;
    Real determinant() const;

    Real components[9];

private:
    // For indexing into the components of the matrix, N * row + column 
    static INT index(INT row, INT column);

    // Support for comparisons
    INT compareArrays(const Matrix3& rightSide) const;
};

template <class Real>
Matrix3<Real> operator* (Real scalar, const Matrix3<Real>& rightSide);

template <class Real>
Vector3<Real> operator* (const Vector3<Real>& vector, const Matrix3<Real>& rightSide);

#include "matrix3.inl"

typedef Matrix3<FLOAT> Matrix3f;
typedef Matrix3<DOUBLE> Matrix3d;

#endif
