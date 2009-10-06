
template <class Real>
Matrix3<Real>::Matrix3(BOOL createIdentity /* = false */)
{
    createIdentity ? makeIdentity() : makeZero();
}

template <class Real>
Matrix3<Real>::Matrix3(const Matrix3& other)
{
    for (INT i = 0; i < 9; ++i)
        components[i] = other.components[i];
}

template <class Real>
Matrix3<Real>::Matrix3(Real a00, Real a01, Real a02,
                       Real a10, Real a11, Real a12, 
                       Real a20, Real a21, Real a22)
{
    components[0] = a00;
    components[1] = a01;
    components[2] = a02;
    components[3] = a10;
    components[4] = a11;
    components[5] = a12;
    components[6] = a20;
    components[7] = a21;
    components[8] = a22;
}

template <class Real>
Matrix3<Real>::Matrix3(const Real values[16], BOOL isRowMajor)
{
    if (isRowMajor)
    {
        for (INT i = 0; i < 9; ++i)
            components[i] = values[i];
    }
    else
    {
        components[0] = values[0];
        components[1] = values[3];
        components[2] = values[6];
        components[3] = values[1];
        components[4] = values[4];
        components[5] = values[7];
        components[6] = values[2];
        components[7] = values[5];
        components[8] = values[8];
    }
}

template <class Real>
Matrix3<Real>::operator const Real* () const
{
    return components;
}

template <class Real>
Matrix3<Real>::operator Real* ()
{
    return components;
}

template <class Real>
const Real* Matrix3<Real>::operator[] (INT row) const
{
    return &components[3 * row];
}

template <class Real>
Real* Matrix3<Real>::operator[] (INT row)
{
    return &components[3 * row];
}

template <class Real>
Real Matrix3<Real>::operator() (INT row, INT column) const
{
    return components[index(row, column)];
}

template <class Real>
Real& Matrix3<Real>::operator() (INT row, INT column)
{
    return components[index(row, column)];
}

template <class Real>
INT Matrix3<Real>::index(INT row, INT column)
{
    assert(row >= 0 && row < 3 && column >= 0 && column < 3 && "Matrix3: index invalid row or column");
    return column + 3 * row;
}

template <class Real>
void Matrix3<Real>::makeZero()
{
    memset(components, 0, 9 * sizeof(Real));
}

template <class Real>
void Matrix3<Real>::makeIdentity()
{
    components[0] = 1.0f;
    components[1] = 0.0f;
    components[2] = 0.0f;
    components[3] = 0.0f;
    components[4] = 1.0f;
    components[5] = 0.0f;
    components[6] = 0.0f;
    components[7] = 0.0f;
    components[8] = 1.0f;
}

template <class Real>
Vector3<Real> Matrix3<Real>::getRow(INT row) const
{
    assert(row >= 0 && row < 3 && "Matrix3: row invalid");
    Vector3<Real> vector;
    for (INT column = 0, i = 3 * row; column < 3; column++, ++i)
        vector[column] = components[i];

    return vector;
}

template <class Real>
Vector3<Real> Matrix3<Real>::getColumn(INT column) const
{
    assert(column >= 0 && column < 3 && "Matrix3: column invalid");
    Vector3<Real> vector;
    for (INT row = 0, i = column; row < 3; row++, i += 3)
        vector[row] = components[i];

    return vector;
}

template <class Real>
void Matrix3<Real>::setRow(INT row, const Vector3<Real>& vector)
{
    assert(row >= 0 && row < 3 && "Matrix3: row invalid");
    for (INT column = 0, i = 3 * row; column < 3; column++, ++i)
        components[i] = vector[column];
}

template <class Real>
void Matrix3<Real>::setColumn(INT column, const Vector3<Real>& vector)
{
    assert(column >= 0 && column < 3 && "Matrix3: column invalid");
    for (INT row = 0, i = column; row < 3; row++, i += 3)
        components[i] = vector[row];
}


template <class Real>
void Matrix3<Real>::getColumnMajor(Real* columnMajor) const
{
    for (INT row = 0, i = 0; row < 3; ++row)
        for (INT column = 0; column < 3; ++column)
            columnMajor[++i] = components[index(column, row)];
}

template <class Real>
Matrix3<Real>& Matrix3<Real>::operator=(const Matrix3& other)
{
    for (INT i = 0; i < 9; ++i)
        components[i] = other.components[i];

    return *this;
}

template <class Real>
INT Matrix3<Real>::compareArrays(const Matrix3& matrix) const
{
    return memcmp(components, matrix.components, 9 * sizeof(Real));
}

template <class Real>
BOOL Matrix3<Real>::operator== (const Matrix3& other) const
{
    return compareArrays(other) == 0;
}

template <class Real>
BOOL Matrix3<Real>::operator!= (const Matrix3& other) const
{
    return compareArrays(other) != 0;
}

template <class Real>
BOOL Matrix3<Real>::operator<  (const Matrix3& other) const
{
    return compareArrays(other) < 0;
}

template <class Real>
BOOL Matrix3<Real>::operator<= (const Matrix3& other) const
{
    return compareArrays(other) <= 0;
}

template <class Real>
BOOL Matrix3<Real>::operator>  (const Matrix3& other) const
{
    return compareArrays(other) > 0;
}

template <class Real>
BOOL Matrix3<Real>::operator>= (const Matrix3& other) const
{
    return compareArrays(other) >= 0;
}

template <class Real>
Matrix3<Real> Matrix3<Real>::operator+ (const Matrix3& other) const
{
    Matrix3 sum;
    for (INT i = 0; i < 9; ++i)
        sum.components[i] = components[i] + other.components[i];

    return sum;
}

template <class Real>
Matrix3<Real> Matrix3<Real>::operator- (const Matrix3& other) const
{
    Matrix3 difference;
    for (INT i = 0; i < 9; ++i)
        difference.components[i] = components[i] - other.components[i];

    return difference;
}

template <class Real>
Matrix3<Real> Matrix3<Real>::operator* (const Matrix3& other) const
{
    Matrix3 product;
    for (INT row = 0; row < 3; ++row)
    {
        for (INT column = 0; column < 3; ++column)
        {
            INT i = index(row, column);
            product.components[i] = 0.0f;
            for (INT mid = 0; mid < 3; ++mid)
                product.components[i] += components[index(row, mid)] * other.components[index(mid, column)];
        }
    }
    return kProd;
}

template <class Real>
Matrix3<Real> Matrix3<Real>::operator* (Real scalar) const
{
    Matrix3 product;
    for (INT i = 0; i < 9; ++i)
        product.components[i] = scalar * components[i];

    return product;
}

template <class Real>
Matrix3<Real> Matrix3<Real>::operator/ (Real scalar) const
{
    assert(abs(scalar) > EPSILON && "Matrix3: scalar divider equal or near zero");

    Matrix3 quotient;
    Real invScalar = 1.0f / scalar;
    for (INT i = 0; i < 9; ++i)
        quotient.components[i] = invScalar * components[i];

    return quotient;
}

template <class Real>
Matrix3<Real> Matrix3<Real>::operator- () const
{
    Matrix3 neg;
    for (INT i = 0; i < 9; ++i)
        neg.components[i] = -components[i];

    return neg;
}

template <class Real>
Matrix3<Real>& Matrix3<Real>::operator+= (const Matrix3& other)
{
    for (INT i = 0; i < 9; ++i)
        components[i] += other.components[i];

    return *this;
}

template <class Real>
Matrix3<Real>& Matrix3<Real>::operator-= (const Matrix3& other)
{
    for (INT i = 0; i < 9; ++i)
        components[i] -= other.components[i];

    return *this;
}

template <class Real>
Matrix3<Real>& Matrix3<Real>::operator*= (Real scalar)
{
    for (INT i = 0; i < 9; ++i)
        components[i] *= scalar;

    return *this;
}

template <class Real>
Matrix3<Real>& Matrix3<Real>::operator/= (Real scalar)
{
     assert(abs(scalar) > EPSILON && "Matrix3: scalar divider equal or near zero");

    Real invScalar = 1.0f / scalar;
    for (i = 0; i < 9; ++i)
        components[i] *= invScalar;

    return *this;
}

template <class Real>
Vector3<Real> Matrix3<Real>::operator* (const Vector3<Real>& vector) const
{
    Vector3<Real> product;
    for (INT row = 0; row < 3; ++row)
    {
        product[row] = 0.0f;
        for (INT column = 0; column < 3; column++)
            product[row] += components[index(row, column)] * vector[column];
    }

    return product;
}

template <class Real>
Matrix3<Real> Matrix3<Real>::transpose() const
{
    Matrix3 transpose;
    for (INT row = 0; row < 3; ++row)
        for (INT column = 0; column < 3; ++column)
            transpose.components[index(row, column)] = components[index(column, row)];

    return transpose;
}

template <class Real>
Matrix3<Real> Matrix3<Real>::inverse() const
{
    Matrix3 inverse;

    inverse[0][0] = components[4] * components[8] - components[5] * components[7];
    inverse[0][1] = components[2] * components[7] - components[1] * components[8];
    inverse[0][2] = components[1] * components[5] - components[2] * components[4];
    inverse[1][0] = components[5] * components[6] - components[3] * components[8];
    inverse[1][1] = components[0] * components[8] - components[2] * components[6];
    inverse[1][2] = components[2] * components[3] - components[0] * components[5];
    inverse[2][0] = components[3] * components[7] - components[4] * components[6];
    inverse[2][1] = components[1] * components[6] - components[0] * components[7];
    inverse[2][2] = components[0] * components[4] - components[1] * components[3];

    Real det = components[0] * inverse[0][0] + components[1] * inverse[1][0] + components[2] * inverse[2][0];
    if (abs(det) <= EPSILON)
        return ZERO;

    inverse /= det;
    return inverse;
}

template <class Real>
Matrix3<Real> Matrix3<Real>::adjoint() const
{
    Matrix3 adjoint;

    adjoint[0][0] = components[4] * components[8] - components[5] * components[7];
    adjoint[0][1] = components[2] * components[7] - components[1] * components[8];
    adjoint[0][2] = components[1] * components[5] - components[2] * components[4];
    adjoint[1][0] = components[5] * components[6] - components[3] * components[8];
    adjoint[1][1] = components[0] * components[8] - components[2] * components[6];
    adjoint[1][2] = components[2] * components[3] - components[0] * components[5];
    adjoint[2][0] = components[3] * components[7] - components[4] * components[6];
    adjoint[2][1] = components[1] * components[6] - components[0] * components[7];
    adjoint[2][2] = components[0] * components[4] - components[1] * components[3];

    return adjoint;
}

template <class Real>
Real Matrix3<Real>::determinant() const
{
    Real A = components[4] * components[8] - components[5] * components[7];
    Real B = components[5] * components[6] - components[3] * components[8];
    Real C = components[3] * components[7] - components[4] * components[6];

    return components[0] * A + components[1] * B + components[2] * C;
}

template <class Real>
Matrix3<Real> operator* (Real scalar, const Matrix3<Real>& other)
{
    return other*scalar;
}

template <class Real>
Vector3<Real> operator* (const Vector3<Real>& rightSide, const Matrix3<Real>& other)
{
    return Vector3<Real>(rightSide[0] * other[0][0] + rightSide[1] * other[1][0] + rightSide[2] * other[2][0],
                         rightSide[0] * other[0][1] + rightSide[1] * other[1][1] + rightSide[2] * other[2][1],
                         rightSide[0] * other[0][2] + rightSide[1] * other[1][2] + rightSide[2] * other[2][2]);
}

