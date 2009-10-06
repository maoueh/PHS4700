
//
/// Constructors & Destructor
//

template <class Real>
inline Vector4<Real>::Vector4()
{
    set(0.0f);
}

template <class Real>
inline Vector4<Real>::Vector4(Real x, Real y, Real z, Real w)
{
    set(x, y, z, w);
}

template <class Real>
inline Vector4<Real>::Vector4(Real* coordinates)
{
    set(coordinates);
}
  
template <class Real>   
inline Vector4<Real>::Vector4(Real scalar, Real w)
{
    set(scalar, w);
}

template <class Real>
inline Vector4<Real>::Vector4(const Vector4<Real>& other)
{
    components[0] = other.components[0];
    components[1] = other.components[1];
    components[2] = other.components[2];
    components[3] = other.components[3];
}

//
/// Members access
//

template <class Real>
inline Real  Vector4<Real>::x() const { return components[0]; }

template <class Real>
inline Real& Vector4<Real>::x()       { return components[0]; }

template <class Real>
inline Real  Vector4<Real>::y() const { return components[1]; }

template <class Real>
inline Real& Vector4<Real>::y()       { return components[1]; }

template <class Real>
inline Real  Vector4<Real>::z() const { return components[2]; }

template <class Real>
inline Real& Vector4<Real>::z()       { return components[2]; }

template <class Real>
inline Real  Vector4<Real>::w() const { return components[3]; }

template <class Real>
inline Real& Vector4<Real>::w()       { return components[3]; }

template <class Real>
inline void Vector4<Real>::set(Real scalar, Real w /* = 1.0f */)
{
    components[0] = scalar; components[1] = scalar; components[2] = scalar; components[3] = w;
}

template <class Real>
inline void Vector4<Real>::set(Real x, Real y, Real z)
{
    components[0] = x; components[1] = y; components[2] = z;
}

template <class Real>
inline void Vector4<Real>::set(Real x, Real y, Real z, Real w)
{
    components[0] = x; components[1] = y; components[2] = z; components[3] = w;
}

template <class Real>
inline void Vector4<Real>::set(Real* coordinates)
{
    for (INT i = 0; i < 4; ++i)
        components[i] = coordinates[i];
}

template <class Real>
inline void Vector4<Real>::set2(Real* coordinates)
{
    for (INT i = 0; i < 2; ++i)
        components[i] = coordinates[i];
}

template <class Real>
inline void Vector4<Real>::set3(Real* coordinates)
{
    for (INT i = 0; i < 3; ++i)
        components[i] = coordinates[i];
}

template <class Real>
inline void Vector4<Real>::assignTo(Real* values)
{
    for (INT i = 0; i < 4; ++i)
        values[i] = components[i];
}

template <class Real>
inline Real& Vector4<Real>::operator[] (INT index)
{
    assert(index >= 0 && index <= 3 && "Vector: index out of range");
    return components[index];
}

template <class Real>
inline Real Vector4<Real>::operator[] (INT index) const
{
    assert(index >= 0 && index <= 3 && "Vector: index out of range");
    return components[index];
}

template <class Real>
Vector4<Real>::operator const Real* () const
{
    return components;
}

template <class Real>
Vector4<Real>::operator Real* ()
{
    return components;
}

//
/// Assigment operator
//

template <class Real>
inline Vector4<Real>& Vector4<Real>::operator= (const Vector4<Real>& rightSide)
{
    components[0] = rightSide.components[0];
    components[1] = rightSide.components[1];
    components[2] = rightSide.components[2];
    components[3] = rightSide.components[3];
    return *this;
}

//
/// Booleans operators
//

template <class Real>
inline BOOL Vector4<Real>::operator== (const Vector4<Real>& rightSide) const
{
    return abs(components[0] - rightSide.components[0]) < EPSILON && 
           abs(components[1] - rightSide.components[1]) < EPSILON &&
           abs(components[2] - rightSide.components[2]) < EPSILON &&
           abs(components[3] - rightSide.components[3]) < EPSILON;
}

template <class Real>
inline BOOL Vector4<Real>::operator!= (const Vector4<Real>& rightSide) const
{
    return !(*this == rightSide);
}

//
/// Self-update binary operators
//

template <class Real>
inline Vector4<Real>& Vector4<Real>::operator+= (const Vector4<Real>& rightSide)
{
    for (INT i = 0; i < 4; ++i)
        components[i] += rightSide.components[i];
    
    return *this;
}

template <class Real>
inline Vector4<Real>& Vector4<Real>::operator-= (const Vector4<Real>& rightSide)
{
    for (INT i = 0; i < 4; ++i)
        components[i] -= rightSide.components[i];

    return *this;
}

template <class Real>
inline Vector4<Real>& Vector4<Real>::operator*= (Real scalar)
{
    for (INT i = 0; i < 4; ++i)
        components[i] *= scalar;

    return *this;
}

template <class Real>
inline Vector4<Real>& Vector4<Real>::operator/= (Real scalar)
{
    assert(abs(scalar) > EPSILON && "Vector: scalar divider equal or near zero");

    Real invScalar = 1 / scalar;
    return (*this) *= invScalar;
}

//
/// Unary operator
//

template <class Real>
inline Vector4<Real> Vector4<Real>::operator- () const
{
    return Vector4<Real>(-components[0], -components[1], -components[2], -components[3]);
}

//
/// Binary operators
//

template <class Real>
inline Vector4<Real> Vector4<Real>::operator+ (const Vector4& rightSide) const
{
    return Vector4<Real>(components[0] + rightSide.components[0], 
                         components[1] + rightSide.components[1], 
                         components[2] + rightSide.components[2], 
                         components[3] + rightSide.components[3]);
}

template <class Real>
inline Vector4<Real> Vector4<Real>::operator- (const Vector4& rightSide) const
{
    return Vector4<Real>(components[0] - rightSide.components[0], 
                         components[1] - rightSide.components[1], 
                         components[2] - rightSide.components[2], 
                         components[3] - rightSide.components[3]);
}

template <class Real>
inline Vector4<Real> Vector4<Real>::operator* (Real scalar) const
{
    return Vector4<Real>(components[0] * scalar, 
                         components[1] * scalar, 
                         components[2] * scalar, 
                         components[3] * scalar);
}

template <class Real>
inline Vector4<Real> Vector4<Real>::operator/ (Real scalar) const
{
    assert(abs(scalar) > EPSILON && "Vector4: scalar divider equal or near zero");

    Real invScalar = 1 / scalar;
    return (*this) * invScalar;
}

//
/// Scalar (*|/) Vector operators
//

template <class Real>
inline Vector4<Real> operator* (Real scalar, const Vector4<Real>& rightSide)
{
    return Vector4<Real>(rightSide.components[0] * scalar, 
                         rightSide.components[1] * scalar, 
                         rightSide.components[2] * scalar, 
                         rightSide.components[3] * scalar);
}

template <class Real>
inline Vector4<Real> operator/ (Real scalar, const Vector4<Real>& rightSide)
{
    assert(abs(scalar) > EPSILON && "Vector4: scalar divider equal or near zero");

    Real invScalar = 1 / scalar;
    return invScalar * (*this);
}

//
/// Output stream operator
//

template <class Real>
inline ostream& operator<<(ostream& outputStream, const Vector4<Real>& vector)
{
    outputStream << setprecision(3) 
                 << "[ " << setw( 3 ) 
                 << vector.components[0] << ", " 
                 << vector.components[1] << ", " 
                 << vector.components[2] 
                 << " ]" << setw(0);
    return outputStream;
}

//
/// Scalar/Dot Product and Vector/Cross Product
//

template <class Real>
inline Real Vector4<Real>::scalarProduct(Vector4<Real>& leftSide, const Vector4<Real>& rightSide)
{
    return dotProduct(leftSide, rightSide);
}

template <class Real>
inline Real Vector4<Real>::dotProduct(Vector4<Real>& leftSide, const Vector4<Real>& rightSide)
{
    return leftSide.components[0] * rightSide.components[0] + 
           leftSide.components[1] * rightSide.components[1] + 
           leftSide.components[2] * rightSide.components[2] + 
           leftSide.components[3] * rightSide.components[3];
}

template <class Real>
inline Vector4<Real> Vector4<Real>::vectorProduct(Vector4<Real>& leftSide, const Vector4<Real>& rightSide)
{
    return crossProduct(leftSide, rightSide);
}

template <class Real>
inline Vector4<Real> Vector4<Real>::crossProduct(Vector4<Real>& leftSide, const Vector4<Real>& rightSide)
{
    return Vector4(leftSide.components[1] * rightSide.components[2] - leftSide.components[2] * rightSide.components[1],
                   leftSide.components[2] * rightSide.components[0] - leftSide.components[0] * rightSide.components[2],
                   leftSide.components[0] * rightSide.components[1] - leftSide.components[1] * rightSide.components[0]);
}

//
/// Distance, Magnitude and Length
//

template <class Real>
inline Real Vector4<Real>::distance(Vector4<Real>& leftSide, const Vector4<Real>& rightSide)
{
    return (leftSide - rightSide).magnitude();
}

// Be careful : the length is not squarred, use magnitude for the squarred value
template <class Real>
inline Real Vector4<Real>::length() const
{
    return components[0] * components[0] + 
           components[1] * components[1] + 
           components[2] * components[2];
}

template <class Real>
inline Real Vector4<Real>::magnitude() const
{
    return sqrt(components[0] * components[0] + 
                components[1] * components[1] + 
                components[2] * components[2]);
}

template <class Real>
inline Vector4<Real> Vector4<Real>::normalize() const
{
    Real magn = magnitude();
    if ( magn > EPSILON )
    {
        magn = 1.0f / magn;
        return (*this) * magn;
    }

    return ZERO;
}