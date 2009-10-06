
template <class Real>
Matrix4<Real>::Matrix4(BOOL createIdentity /* = false */)
{
    createIdentity ? makeIdentity() : makeZero();
}

template <class Real>
Matrix4<Real>::Matrix4(const Matrix4& other)
{
    for (INT i = 0; i < 16; ++i)
        components[i] = other.components[i];
}

template <class Real>
Matrix4<Real>::Matrix4(Real a00, Real a01, Real a02, Real a03,
                       Real a10, Real a11, Real a12, Real a13, 
                       Real a20, Real a21, Real a22, Real a23, 
                       Real a30, Real a31, Real a32, Real a33)
{
    components[0] = a00;
    components[1] = a01;
    components[2] = a02;
    components[3] = a03;
    components[4] = a10;
    components[5] = a11;
    components[6] = a12;
    components[7] = a13;
    components[8] = a20;
    components[9] = a21;
    components[10] = a22;
    components[11] = a23;
    components[12] = a30;
    components[13] = a31;
    components[14] = a32;
    components[15] = a33;
}

template <class Real>
Matrix4<Real>::Matrix4(const Real values[16], BOOL isRowMajor)
{
    if (isRowMajor)
    {
        for (INT i = 0; i < 16; ++i)
            components[i] = values[i];
    }
    else
    {
        components[0] = values[0];
        components[1] = values[4];
        components[2] = values[8];
        components[3] = values[12];
        components[4] = values[1];
        components[5] = values[5];
        components[6] = values[9];
        components[7] = values[13];
        components[8] = values[2];
        components[9] = values[6];
        components[10] = values[10];
        components[11] = values[14];
        components[12] = values[3];
        components[13] = values[7];
        components[14] = values[11];
        components[15] = values[15];
    }
}

template <class Real>
Matrix4<Real>::operator const Real* () const
{
    return components;
}

template <class Real>
Matrix4<Real>::operator Real* ()
{
    return components;
}

template <class Real>
const Real* Matrix4<Real>::operator[] (INT row) const
{
    return &components[4 * row];
}

template <class Real>
Real* Matrix4<Real>::operator[] (INT row)
{
    return &components[4 * row];
}

template <class Real>
Real Matrix4<Real>::operator() (INT row, INT column) const
{
    return components[index(row, column)];
}

template <class Real>
Real& Matrix4<Real>::operator() (INT row, INT column)
{
    return components[index(row, column)];
}

template <class Real>
INT Matrix4<Real>::index(INT row, INT column)
{
    assert(row >= 0 && row < 4 && column >= 0 && column < 4 && "Matrix4: index invalid row or column");
    return column + 4 * row;
}

template <class Real>
void Matrix4<Real>::makeZero()
{
    memset(components, 0, 16 * sizeof(Real));
}

template <class Real>
void Matrix4<Real>::makeIdentity()
{
    components[0] = 1.0f;
    components[1] = 0.0f;
    components[2] = 0.0f;
    components[3] = 0.0f;
    components[4] = 0.0f;
    components[5] = 1.0f;
    components[6] = 0.0f;
    components[7] = 0.0f;
    components[8] = 0.0f;
    components[9] = 0.0f;
    components[10] = 1.0f;
    components[11] = 0.0f;
    components[12] = 0.0f;
    components[13] = 0.0f;
    components[14] = 0.0f;
    components[15] = 1.0f;
}

template <class Real>
Vector4<Real> Matrix4<Real>::getRow(INT row) const
{
    assert(row >= 0 && row < 4 && "Matrix4: row invalid");
    Vector4<Real> vector;
    for (INT column = 0, i = 4 * row; column < 4; column++, ++i)
        vector[column] = components[i];

    return vector;
}

template <class Real>
Vector4<Real> Matrix4<Real>::getColumn(INT column) const
{
    assert(column >= 0 && column < 4 && "Matrix4: column invalid");
    Vector4<Real> vector;
    for (INT row = 0, i = column; row < 4; row++, i += 4)
        vector[row] = components[i];

    return vector;
}

template <class Real>
void Matrix4<Real>::setRow(INT row, const Vector4<Real>& vector)
{
    assert(row >= 0 && row < 4 && "Matrix4: row invalid");
    for (INT column = 0, i = 4 * row; column < 4; column++, ++i)
        components[i] = vector[column];
}

template <class Real>
void Matrix4<Real>::setColumn(INT column, const Vector4<Real>& vector)
{
    assert(column >= 0 && column < 4 && "Matrix4: column invalid");
    for (INT row = 0, i = column; row < 4; row++, i += 4)
        components[i] = vector[row];
}


template <class Real>
void Matrix4<Real>::getColumnMajor(Real* columnMajor) const
{
    for (INT row = 0, i = 0; row < 4; ++row)
        for (INT column = 0; column < 4; ++column)
            columnMajor[++i] = components[index(column, row)];
}

template <class Real>
Matrix4<Real>& Matrix4<Real>::operator=(const Matrix4& other)
{
    for (INT i = 0; i < 16; ++i)
        components[i] = other.components[i];

    return *this;
}

template <class Real>
INT Matrix4<Real>::compareArrays(const Matrix4& matrix) const
{
    return memcmp(components, matrix.components, 16 * sizeof(Real));
}

template <class Real>
BOOL Matrix4<Real>::operator== (const Matrix4& other) const
{
    return compareArrays(other) == 0;
}

template <class Real>
BOOL Matrix4<Real>::operator!= (const Matrix4& other) const
{
    return compareArrays(other) != 0;
}

template <class Real>
BOOL Matrix4<Real>::operator<  (const Matrix4& other) const
{
    return compareArrays(other) < 0;
}

template <class Real>
BOOL Matrix4<Real>::operator<= (const Matrix4& other) const
{
    return compareArrays(other) <= 0;
}

template <class Real>
BOOL Matrix4<Real>::operator>  (const Matrix4& other) const
{
    return compareArrays(other) > 0;
}

template <class Real>
BOOL Matrix4<Real>::operator>= (const Matrix4& other) const
{
    return compareArrays(other) >= 0;
}

template <class Real>
Matrix4<Real> Matrix4<Real>::operator+ (const Matrix4& other) const
{
    Matrix4 sum;
    for (INT i = 0; i < 16; ++i)
        sum.components[i] = components[i] + other.components[i];

    return sum;
}

template <class Real>
Matrix4<Real> Matrix4<Real>::operator- (const Matrix4& other) const
{
    Matrix4 difference;
    for (INT i = 0; i < 16; ++i)
        difference.components[i] = components[i] - other.components[i];

    return difference;
}

template <class Real>
Matrix4<Real> Matrix4<Real>::operator* (const Matrix4& other) const
{
    Matrix4 product;
    for (INT row = 0; row < 4; ++row)
    {
        for (INT column = 0; column < 4; ++column)
        {
            INT i = index(row, column);
            product.components[i] = 0.0f;
            for (INT mid = 0; mid < 4; ++mid)
                product.components[i] += components[index(row, mid)] * other.components[index(mid, column)];
        }
    }
    return kProd;
}

template <class Real>
Matrix4<Real> Matrix4<Real>::operator* (Real scalar) const
{
    Matrix4 product;
    for (INT i = 0; i < 16; ++i)
        product.components[i] = scalar * components[i];

    return product;
}

template <class Real>
Matrix4<Real> Matrix4<Real>::operator/ (Real scalar) const
{
    assert(abs(scalar) > EPSILON && "Matrix4: scalar divider equal or near zero");

    Matrix4 quotient;
    Real invScalar = 1.0f / scalar;
    for (INT i = 0; i < 16; ++i)
        quotient.components[i] = invScalar * components[i];

    return quotient;
}

template <class Real>
Matrix4<Real> Matrix4<Real>::operator- () const
{
    Matrix4 neg;
    for (INT i = 0; i < 16; ++i)
        neg.components[i] = -components[i];

    return neg;
}

template <class Real>
Matrix4<Real>& Matrix4<Real>::operator+= (const Matrix4& other)
{
    for (INT i = 0; i < 16; ++i)
        components[i] += other.components[i];

    return *this;
}

template <class Real>
Matrix4<Real>& Matrix4<Real>::operator-= (const Matrix4& other)
{
    for (INT i = 0; i < 16; ++i)
        components[i] -= other.components[i];

    return *this;
}

template <class Real>
Matrix4<Real>& Matrix4<Real>::operator*= (Real scalar)
{
    for (INT i = 0; i < 16; ++i)
        components[i] *= scalar;

    return *this;
}

template <class Real>
Matrix4<Real>& Matrix4<Real>::operator/= (Real scalar)
{
     assert(abs(scalar) > EPSILON && "Matrix4: scalar divider equal or near zero");

    Real invScalar = 1.0f / scalar;
    for (i = 0; i < 16; ++i)
        components[i] *= invScalar;

    return *this;
}

template <class Real>
Vector4<Real> Matrix4<Real>::operator* (const Vector4<Real>& vector) const
{
    Vector4<Real> product;
    for (INT row = 0; row < 4; ++row)
    {
        product[row] = 0.0f;
        for (INT column = 0; column < 4; column++)
            product[row] += components[index(row, column)] * vector[column];
    }

    return product;
}

template <class Real>
Matrix4<Real> Matrix4<Real>::transpose() const
{
    Matrix4 transpose;
    for (INT row = 0; row < 4; ++row)
        for (INT column = 0; column < 4; ++column)
            transpose.components[index(row, column)] = components[index(column, row)];

    return transpose;
}

template <class Real>
Matrix4<Real> Matrix4<Real>::inverse() const
{
    Real A0 = components[0]  * components[5]  - components[1]  * components[4];
    Real A1 = components[0]  * components[6]  - components[2]  * components[4];
    Real A2 = components[0]  * components[7]  - components[3]  * components[4];
    Real A3 = components[1]  * components[6]  - components[2]  * components[5];
    Real A4 = components[1]  * components[7]  - components[3]  * components[5];
    Real A5 = components[2]  * components[7]  - components[3]  * components[6];
    Real B0 = components[8]  * components[13] - components[9]  * components[12];
    Real B1 = components[8]  * components[14] - components[10] * components[12];
    Real B2 = components[8]  * components[15] - components[11] * components[12];
    Real B3 = components[9]  * components[14] - components[10] * components[13];
    Real B4 = components[9]  * components[15] - components[11] * components[13];
    Real B5 = components[10] * components[15] - components[11] * components[14];

    Real det = A0 * B5 - A1 * B4 + A2 * B3 + A3 * B2 - A4 * B1 + A5 * B0;
    if (abs(det) <= EPSILON)
        return Matrix4<Real>::ZERO;

    Matrix4 inverse;
    inverse[0][0] = + components[5]  * B5  - components[6]  * B4 + components[7]  * B3;
    inverse[1][0] = - components[4]  * B5  + components[6]  * B2 - components[7]  * B1;
    inverse[2][0] = + components[4]  * B4  - components[5]  * B2 + components[7]  * B0;
    inverse[3][0] = - components[4]  * B3  + components[5]  * B1 - components[6]  * B0;
    inverse[0][1] = - components[1]  * B5  + components[2]  * B4 - components[3]  * B3;
    inverse[1][1] = + components[0]  * B5  - components[2]  * B2 + components[3]  * B1;
    inverse[2][1] = - components[0]  * B4  + components[1]  * B2 - components[3]  * B0;
    inverse[3][1] = + components[0]  * B3  - components[1]  * B1 + components[2]  * B0;
    inverse[0][2] = + components[13] * A5  - components[14] * A4 + components[15] * A3;
    inverse[1][2] = - components[12] * A5  + components[14] * A2 - components[15] * A1;
    inverse[2][2] = + components[12] * A4  - components[13] * A2 + components[15] * A0;
    inverse[3][2] = - components[12] * A3  + components[13] * A1 - components[14] * A0;
    inverse[0][3] = - components[9]  * A5  + components[10] * A4 - components[11] * A3;
    inverse[1][3] = + components[8]  * A5  - components[10] * A2 + components[11] * A1;
    inverse[2][3] = - components[8]  * A4  + components[9]  * A2 - components[11] * A0;
    inverse[3][3] = + components[8]  * A3  - components[9]  * A1 + components[10] * A0;

    Real invDet = 1.0f / det;
    for (INT row = 0; row < 4; ++row)
        for (INT column = 0; column < 4; ++column)
            inverse[row][column] *= invDet;

    return inverse;
}

template <class Real>
Matrix4<Real> Matrix4<Real>::adjoint() const
{
    Real A0 = components[0]  * components[5]  - components[1]  * components[4];
    Real A1 = components[0]  * components[6]  - components[2]  * components[4];
    Real A2 = components[0]  * components[7]  - components[3]  * components[4];
    Real A3 = components[1]  * components[6]  - components[2]  * components[5];
    Real A4 = components[1]  * components[7]  - components[3]  * components[5];
    Real A5 = components[2]  * components[7]  - components[3]  * components[6];
    Real B0 = components[8]  * components[13] - components[9]  * components[12];
    Real B1 = components[8]  * components[14] - components[10] * components[12];
    Real B2 = components[8]  * components[15] - components[11] * components[12];
    Real B3 = components[9]  * components[14] - components[10] * components[13];
    Real B4 = components[9]  * components[15] - components[11] * components[13];
    Real B5 = components[10] * components[15] - components[11] * components[14];

    Matrix4 adjoint;
    adjoint[0][0] = + components[5]  * B5 - components[6]  * B4 + components[7]  * B3;
    adjoint[1][0] = - components[4]  * B5 + components[6]  * B2 - components[7]  * B1;
    adjoint[2][0] = + components[4]  * B4 - components[5]  * B2 + components[7]  * B0;
    adjoint[3][0] = - components[4]  * B3 + components[5]  * B1 - components[6]  * B0;
    adjoint[0][1] = - components[1]  * B5 + components[2]  * B4 - components[3]  * B3;
    adjoint[1][1] = + components[0]  * B5 - components[2]  * B2 + components[3]  * B1;
    adjoint[2][1] = - components[0]  * B4 + components[1]  * B2 - components[3]  * B0;
    adjoint[3][1] = + components[0]  * B3 - components[1]  * B1 + components[2]  * B0;
    adjoint[0][2] = + components[13] * A5 - components[14] * A4 + components[15] * A3;
    adjoint[1][2] = - components[12] * A5 + components[14] * A2 - components[15] * A1;
    adjoint[2][2] = + components[12] * A4 - components[13] * A2 + components[15] * A0;
    adjoint[3][2] = - components[12] * A3 + components[13] * A1 - components[14] * A0;
    adjoint[0][3] = - components[9]  * A5 + components[10] * A4 - components[11] * A3;
    adjoint[1][3] = + components[8]  * A5 - components[10] * A2 + components[11] * A1;
    adjoint[2][3] = - components[8]  * A4 + components[9]  * A2 - components[11] * A0;
    adjoint[3][3] = + components[8]  * A3 - components[9]  * A1 + components[10] * A0;

    return adjoint;
}

template <class Real>
Real Matrix4<Real>::determinant() const
{
    Real A0 = components[0]  * components[5]  - components[1]  * components[4];
    Real A1 = components[0]  * components[6]  - components[2]  * components[4];
    Real A2 = components[0]  * components[7]  - components[3]  * components[4];
    Real A3 = components[1]  * components[6]  - components[2]  * components[5];
    Real A4 = components[1]  * components[7]  - components[3]  * components[5];
    Real A5 = components[2]  * components[7]  - components[3]  * components[6];
    Real B0 = components[8]  * components[13] - components[9]  * components[12];
    Real B1 = components[8]  * components[14] - components[10] * components[12];
    Real B2 = components[8]  * components[15] - components[11] * components[12];
    Real B3 = components[9]  * components[14] - components[10] * components[13];
    Real B4 = components[9]  * components[15] - components[11] * components[13];
    Real B5 = components[10] * components[15] - components[11] * components[14];

    return A0 * B5 - A1 * B4 + A2 * B3 + A3 * B2 - A4 * B1 + A5 * B0;
}

template <class Real>
Matrix4<Real> operator* (Real scalar, const Matrix4<Real>& other)
{
    return other*scalar;
}

template <class Real>
Vector4<Real> operator* (const Vector4<Real>& rightSide, const Matrix4<Real>& other)
{
    return Vector4<Real>(rightSide[0] * other[0][0] + rightSide[1] * other[1][0] + 
                         rightSide[2] * other[2][0] + rightSide[3] * other[3][0],

                         rightSide[0] * other[0][1] + rightSide[1] * other[1][1] + 
                         rightSide[2] * other[2][1] + rightSide[3] * other[3][1],

                         rightSide[0] * other[0][2] + rightSide[1] * other[1][2] + 
                         rightSide[2] * other[2][2] + rightSide[3] * other[3][2],

                         rightSide[0] * other[0][3] + rightSide[1] * other[1][3] + 
                         rightSide[2] * other[2][3] + rightSide[3] * other[3][3]);
}

