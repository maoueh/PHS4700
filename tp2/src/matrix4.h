#ifndef MATRIX4_H
#define MATRIX4_H

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

#include "common.h"
#include "vector4.h"

template <class Real>
class Matrix4
{
public:
    static const Matrix4 ZERO;
    static const Matrix4 IDENTITY;
    
    // If createIdentity is true, create the identity matrix. Otherwise, create the zero matrix.
    Matrix4 (BOOL createIdentity = false);
    Matrix4 (const Matrix4& rightSide);

    // Input read in row-major order
    Matrix4 (Real a00, Real a01, Real a02, Real a03,
             Real a10, Real a11, Real a12, Real a13,
             Real a20, Real a21, Real a22, Real a23,
             Real a30, Real a31, Real a32, Real a33);

    // Create a matrix from an array of numbers. The input array is
    // INTerpreted based on the isRowMajor input as
    //   true:  entry[0..15]={a00,a01,a02,a03,a10,a11,a12,a13,a20,a21,a22,
    //                        a23,a30,a31,a32,a33} [row major order]
    //   false: entry[0..15]={a00,a10,a20,a30,a01,a11,a21,a31,a02,a12,a22,
    //                        a32,a03,a13,a23,a33} [column major order]
    Matrix4 (const Real values[16], BOOL isRowMajor);

    void makeZero();
    void makeIdentity();

    operator const Real*() const;
    operator Real*();
    const Real* operator[] (INT row) const;
    Real* operator[] (INT row);
    Real  operator() (INT row, INT column) const;
    Real& operator() (INT row, INT column);

    Vector4<Real> getRow(INT row) const;
    Vector4<Real> getColumn(INT column) const;

    void setRow(INT row, const Vector4<Real>& rightSide);
    void setColumn(INT column, const Vector4<Real>& rightSide);
    
    void getColumnMajor(Real* columnMajor) const;

    Matrix4& operator= (const Matrix4& rightSide);

    BOOL operator== (const Matrix4& rightSide) const;
    BOOL operator!= (const Matrix4& rightSide) const;
    BOOL operator<  (const Matrix4& rightSide) const;
    BOOL operator<= (const Matrix4& rightSide) const;
    BOOL operator>  (const Matrix4& rightSide) const;
    BOOL operator>= (const Matrix4& rightSide) const;

    Vector4<Real> operator* (const Vector4<Real>& vector) const;  // M * v

    Matrix4 operator+ (const Matrix4& rightSide) const;
    Matrix4 operator- (const Matrix4& rightSide) const;
    Matrix4 operator* (const Matrix4& rightSide) const;
    Matrix4 operator* (Real scalar) const;
    Matrix4 operator/ (Real scalar) const;
    Matrix4 operator- () const;

    Matrix4& operator+= (const Matrix4& rightSide);
    Matrix4& operator-= (const Matrix4& rightSide);
    Matrix4& operator*= (Real scalar);
    Matrix4& operator/= (Real scalar);

    Matrix4 transpose() const;
    Matrix4 inverse() const;
    Matrix4 adjoint() const;
    Real determinant() const;

    Real components[16];

private:
    // For indexing into the components of the matrix, N * row + column 
    static INT index(INT row, INT column);

    // support for comparisons
    INT compareArrays(const Matrix4& rightSide) const;
};

template <class Real>
Matrix4<Real> operator* (Real scalar, const Matrix4<Real>& rightSide);

template <class Real>
Vector4<Real> operator* (const Vector4<Real>& vector, const Matrix4<Real>& rightSide);

#include "matrix4.inl"

typedef Matrix4<FLOAT> Matrix4f;
typedef Matrix4<DOUBLE> Matrix4d;

#endif
