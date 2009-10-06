
//
/// Constructors & Destructor
//

template <class Real>
inline Vector3<Real>::Vector3()
{
    set(0.0f);
}

template <class Real>
inline Vector3<Real>::Vector3(Real x, Real y, Real z)
{
    set(x, y, z);
}

template <class Real>
inline Vector3<Real>::Vector3(Real* coordinates)
{
    set(coordinates);
}
  
template <class Real>   
inline Vector3<Real>::Vector3(Real scalar)
{
    set(scalar);
}

template <class Real>
inline Vector3<Real>::Vector3(const Vector3<Real>& other)
{
    components[0] = other.components[0];
    components[1] = other.components[1];
    components[2] = other.components[2];
}

//
/// Members access
//

template <class Real>
inline Real  Vector3<Real>::x() const { return components[0]; }

template <class Real>
inline Real& Vector3<Real>::x()       { return components[0]; }

template <class Real>
inline Real  Vector3<Real>::y() const { return components[1]; }

template <class Real>
inline Real& Vector3<Real>::y()       { return components[1]; }

template <class Real>
inline Real  Vector3<Real>::z() const { return components[2]; }

template <class Real>
inline Real& Vector3<Real>::z()       { return components[2]; }

template <class Real>
inline void Vector3<Real>::set(Real scalar)
{
    components[0] = scalar; components[1] = scalar; components[2] = scalar;;
}

template <class Real>
inline void Vector3<Real>::set(Real x, Real y, Real z)
{
    components[0] = x; components[1] = y; components[2] = z;
}

template <class Real>
inline void Vector3<Real>::set(Real* coordinates)
{
    for (INT i = 0; i < 3; ++i)
        components[i] = coordinates[i];
}

template <class Real>
inline void Vector3<Real>::set2(Real* coordinates)
{
    for (INT i = 0; i < 2; ++i)
        components[i] = coordinates[i];
}

template <class Real>
inline void Vector3<Real>::assignTo(Real* values)
{
    for (INT i = 0; i < 3; ++i)
        values[i] = components[i];
}

template <class Real>
inline Real& Vector3<Real>::operator[] (INT index)
{
    assert(index >= 0 && index <= 2 && "Vector: index out of range");
    return components[index];
}

template <class Real>
inline Real Vector3<Real>::operator[] (INT index) const
{
    assert(index >= 0 && index <= 2 && "Vector: index out of range");
    return components[index];
}

template <class Real>
Vector3<Real>::operator const Real* () const
{
    return components;
}

template <class Real>
Vector3<Real>::operator Real* ()
{
    return components;
}

//
/// Assigment operator
//

template <class Real>
inline Vector3<Real>& Vector3<Real>::operator= (const Vector3<Real>& rightSide)
{
    components[0] = rightSide.components[0];
    components[1] = rightSide.components[1];
    components[2] = rightSide.components[2];
    return *this;
}

//
/// Booleans operators
//

template <class Real>
inline BOOL Vector3<Real>::operator== (const Vector3<Real>& rightSide) const
{
    return abs(components[0] - rightSide.components[0]) < EPSILON && 
           abs(components[1] - rightSide.components[1]) < EPSILON &&
           abs(components[2] - rightSide.components[2]) < EPSILON;
}

template <class Real>
inline BOOL Vector3<Real>::operator!= (const Vector3<Real>& rightSide) const
{
    return !(*this == rightSide);
}

//
/// Self-update binary operators
//

template <class Real>
inline Vector3<Real>& Vector3<Real>::operator+= (const Vector3<Real>& rightSide)
{
    components[0] += rightSide.components[0];
    components[1] += rightSide.components[1];
    components[2] += rightSide.components[2];
    return *this;
}

template <class Real>
inline Vector3<Real>& Vector3<Real>::operator-= (const Vector3<Real>& rightSide)
{
    components[0] -= rightSide.components[0];
    components[1] -= rightSide.components[1];
    components[2] -= rightSide.components[2];
    return *this;
}

template <class Real>
inline Vector3<Real>& Vector3<Real>::operator*= (Real scalar)
{
    components[0] *= scalar;
    components[1] *= scalar;
    components[2] *= scalar;
    return *this;
}

template <class Real>
inline Vector3<Real>& Vector3<Real>::operator/= (Real scalar)
{
    assert(abs(scalar) > EPSILON && "Vector: scalar divider equal or near zero");

    Real invScalar = 1 / scalar;
    return (*this) *= invScalar;
}

//
/// Unary operator
//

template <class Real>
inline Vector3<Real> Vector3<Real>::operator- () const
{
    return Vector3<Real>(-components[0], -components[1], -components[2]);
}

//
/// Binary operators
//

template <class Real>
inline Vector3<Real> Vector3<Real>::operator+ (const Vector3& rightSide) const
{
    return Vector3<Real>(components[0] + rightSide.components[0], 
                         components[1] + rightSide.components[1], 
                         components[2] + rightSide.components[2]);
}

template <class Real>
inline Vector3<Real> Vector3<Real>::operator- (const Vector3& rightSide) const
{
    return Vector3<Real>(components[0] - rightSide.components[0], 
                         components[1] - rightSide.components[1], 
                         components[2] - rightSide.components[2]);
}

template <class Real>
inline Vector3<Real> Vector3<Real>::operator* (Real scalar) const
{
    return Vector3<Real>(components[0] * scalar, 
                         components[1] * scalar, 
                         components[2] * scalar);
}

template <class Real>
inline Vector3<Real> Vector3<Real>::operator/ (Real scalar) const
{
    assert(abs(scalar) > EPSILON && "Vector3: scalar divider equal or near zero");

    Real invScalar = 1 / scalar;
    return (*this) * invScalar;
}

//
/// Scalar (*|/) Vector operators
//

template <class Real>
inline Vector3<Real> operator* (Real scalar, const Vector3<Real>& rightSide)
{
    return Vector3<Real>(rightSide.components[0] * scalar, 
                         rightSide.components[1] * scalar, 
                         rightSide.components[2] * scalar);
}

template <class Real>
inline Vector3<Real> operator/ (Real scalar, const Vector3<Real>& rightSide)
{
    assert(abs(scalar) > EPSILON && "Vector3: scalar divider equal or near zero");

    Real invScalar = 1 / scalar;
    return invScalar * (*this);
}

//
/// Output stream operator
//

template <class Real>
inline ostream& operator<<(ostream& outputStream, const Vector3<Real>& vector)
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
inline Real Vector3<Real>::scalarProduct(Vector3<Real>& leftSide, const Vector3<Real>& rightSide)
{
    return dotProduct(leftSide, rightSide);
}

template <class Real>
inline Real Vector3<Real>::dotProduct(Vector3<Real>& leftSide, const Vector3<Real>& rightSide)
{
    return leftSide.components[0] * rightSide.components[0] + 
           leftSide.components[1] * rightSide.components[1] + 
           leftSide.components[2] * rightSide.components[2];
}

template <class Real>
inline Vector3<Real> Vector3<Real>::vectorProduct(Vector3<Real>& leftSide, const Vector3<Real>& rightSide)
{
    return crossProduct(leftSide, rightSide);
}

template <class Real>
inline Vector3<Real> Vector3<Real>::crossProduct(Vector3<Real>& leftSide, const Vector3<Real>& rightSide)
{
    return Vector3(leftSide.components[1] * rightSide.components[2] - leftSide.components[2] * rightSide.components[1],
                   leftSide.components[2] * rightSide.components[0] - leftSide.components[0] * rightSide.components[2],
                   leftSide.components[0] * rightSide.components[1] - leftSide.components[1] * rightSide.components[0]);
}

//
/// Distance, Magnitude and Length
//

template <class Real>
inline Real Vector3<Real>::distance(Vector3<Real>& leftSide, const Vector3<Real>& rightSide)
{
    return (leftSide - rightSide).magnitude();
}

// Be careful : the length is not squarred, use magnitude for the squarred value
template <class Real>
inline Real Vector3<Real>::length() const
{
    return components[0] * components[0] + 
           components[1] * components[1] + 
           components[2] * components[2];
}

template <class Real>
inline Real Vector3<Real>::magnitude() const
{
    return sqrt(components[0] * components[0] + 
                components[1] * components[1] + 
                components[2] * components[2]);
}

template <class Real>
inline Vector3<Real> Vector3<Real>::normalize() const
{
    Real magn = magnitude();
    if ( magn > EPSILON )
    {
        magn = 1.0f / magn;
        return (*this) * magn;
    }

    return ZERO;
}