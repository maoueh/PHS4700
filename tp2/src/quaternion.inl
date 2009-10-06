
//
/// Constructors & Destructor
//

template <class Real>
Quaternion<Real>::Quaternion()
{
    // Uninitialized for better performance
}

template <class Real>
Quaternion<Real>::Quaternion(Real w, Real x, Real y, Real z)
{
    components[0] = w;
    components[1] = x;
    components[2] = y;
    components[3] = z;
}

template <class Real>
Quaternion<Real>::Quaternion(Real angle, const Vector3<Real>& axis)
{
    Real halfAngle = angle * 0.5f;
    Vector3<Real> result = sin(halfAngle) * axis.normalize();
    components[0] = cos(halfAngle);
    components[1] = result.x();
    components[2] = result.y();
    components[3] = result.z();
}

template <class Real>
Quaternion<Real>::Quaternion(Real angle, const Vector4<Real>& axis)
{
    Real halfAngle = angle * 0.5f;
    Vector4<Real> result = sin(halfAngle) * axis.normalize();
    components[0] = cos(halfAngle);
    components[1] = result.x();
    components[2] = result.y();
    components[3] = result.z();
}

template <class Real>
Quaternion<Real>::Quaternion(Real* values)
{
    components[0] = values[0];
    components[1] = values[1];
    components[2] = values[2];
    components[3] = values[3];
}

template <class Real>
Quaternion<Real>::Quaternion(const Quaternion& rightSide)
{
    components[0] = rightSide.components[0];
    components[1] = rightSide.components[1];
    components[2] = rightSide.components[2];
    components[3] = rightSide.components[3];
}

//
/// Members access
//

template <class Real>
Quaternion<Real>::operator const Real*() const
{
    return components;
}

template <class Real>
Quaternion<Real>::operator Real*()
{
    return components;
}

template <class Real>
Real Quaternion<Real>::operator[] (int index) const
{
    assert(index >= 0 && index <= 3 && "Quaternion: index out of range");
    return components[index];
}

template <class Real>
Real& Quaternion<Real>::operator[] (int index)
{
    assert(index >= 0 && index <= 3 && "Quaternion: index out of range");
    return components[index];
}

template <class Real>
Real Quaternion<Real>::w() const
{
    return components[0];
}

template <class Real>
Real& Quaternion<Real>::w()
{
    return components[0];
}

template <class Real>
Real Quaternion<Real>::x() const
{
    return components[1];
}

template <class Real>
Real& Quaternion<Real>::x()
{
    return components[1];
}

template <class Real>
Real Quaternion<Real>::y() const
{
    return components[2];
}

template <class Real>
Real& Quaternion<Real>::y()
{
    return components[2];
}

template <class Real>
Real Quaternion<Real>::z() const
{
    return components[3];
}

template <class Real>
Real& Quaternion<Real>::z()
{
    return components[3];
}

template <class Real>
void Quaternion<Real>::assignTo(Real* values)
{
    for(int i = 0; i < 4; ++i)
        values[i] = components[i];
}

template <class Real>
void Quaternion<Real>::set(Real* values)
{
    for(int i = 0; i < 4; ++i)
        components[i] = values[i];
}

template <class Real>
void Quaternion<Real>::set(Real w, Real x, Real y, Real z)
{
    components[0] = w;
    components[1] = x;
    components[2] = y;
    components[3] = z;
}

//
/// Assigment operator
//

template <class Real>
Quaternion<Real>& Quaternion<Real>::operator= (const Quaternion& rightSide)
{
    components[0] = rightSide.components[0];
    components[1] = rightSide.components[1];
    components[2] = rightSide.components[2];
    components[3] = rightSide.components[3];
    return *this;
}

//
/// Boolean operators
//

template <class Real>
int Quaternion<Real>::compareArrays(const Quaternion& rightSide) const
{
    return memcmp(components, rightSide.components, 4 * sizeof(Real));
}

template <class Real>
bool Quaternion<Real>::operator== (const Quaternion& rightSide) const
{
    return compareArrays(rightSide) == 0;
}

template <class Real>
bool Quaternion<Real>::operator!= (const Quaternion& rightSide) const
{
    return compareArrays(rightSide) != 0;
}

template <class Real>
bool Quaternion<Real>::operator< (const Quaternion& rightSide) const
{
    return compareArrays(rightSide) < 0;
}

template <class Real>
bool Quaternion<Real>::operator<= (const Quaternion& rightSide) const
{
    return compareArrays(rightSide) <= 0;
}

template <class Real>
bool Quaternion<Real>::operator> (const Quaternion& rightSide) const
{
    return compareArrays(rightSide) > 0;
}

template <class Real>
bool Quaternion<Real>::operator>= (const Quaternion& rightSide) const
{
    return compareArrays(rightSide) >= 0;
}

//
/// Binary operators
//

template <class Real>
Quaternion<Real> Quaternion<Real>::operator+ (const Quaternion& rightSide) const
{
    Quaternion sum;
    for (int i = 0; i < 4; ++i)
        sum.components[i] = components[i] + rightSide.components[i];

    return sum;
}

template <class Real>
Quaternion<Real> Quaternion<Real>::operator- (const Quaternion& rightSide) const
{
    Quaternion diff;
    for (int i = 0; i < 4; ++i)
        diff.components[i] = components[i] - rightSide.components[i];

    return diff;
}

template <class Real>
Quaternion<Real> Quaternion<Real>::operator* (const Quaternion& rightSide) const
{
    Quaternion prod;
    prod.components[0] = components[0] * rightSide.components[0] -
                         components[1] * rightSide.components[1] -
                         components[2] * rightSide.components[2] -
                         components[3] * rightSide.components[3];

    prod.components[1] = components[0] * rightSide.components[1] +
                         components[1] * rightSide.components[0] +
                         components[2] * rightSide.components[3] -
                         components[3] * rightSide.components[2];

    prod.components[2] = components[0] * rightSide.components[2] +
                         components[2] * rightSide.components[0] +
                         components[3] * rightSide.components[1] -
                         components[1] * rightSide.components[3];

    prod.components[3] = components[0] * rightSide.components[3] +
                         components[3] * rightSide.components[0] +
                         components[1] * rightSide.components[2] -
                         components[2] * rightSide.components[1];
    return prod;
}

template <class Real>
Quaternion<Real> Quaternion<Real>::operator* (Real scalar) const
{
    Quaternion prod;
    for (int i = 0; i < 4; ++i)
        prod.components[i] = scalar * components[i];

    return prod;
}

template <class Real>
Quaternion<Real> Quaternion<Real>::operator/ (Real scalar) const
{
    assert(abs(scalar) > EPSILON && "Quaternion: scalar divider equal or near zero");

    Quaternion quot;
    Real invScalar = 1.0f / scalar;
    for (int i = 0; i < 4; ++i)
        quot.components[i] = invScalar * components[i];

    return quot;
}

template <class Real>
Quaternion<Real> operator* (Real scalar, const Quaternion<Real>& rightSide)
{
    Quaternion<Real> prod;
    for (int i = 0; i < 4; ++i)
        prod[i] = scalar * rightSide[i];

    return prod;
}

//
/// Unary operator
//

template <class Real>
Quaternion<Real> Quaternion<Real>::operator- () const
{
    Quaternion neg;
    for (int i = 0; i < 4; ++i)
        neg.components[i] = -components[i];

    return neg;
}

//
/// Binary self-update operator
//

template <class Real>
Quaternion<Real>& Quaternion<Real>::operator+= (const Quaternion& rightSide)
{
    for (int i = 0; i < 4; ++i)
        components[i] += rightSide.components[i];

    return *this;
}

template <class Real>
Quaternion<Real>& Quaternion<Real>::operator-= (const Quaternion& rightSide)
{
    for (int i = 0; i < 4; ++i)
        components[i] -= rightSide.components[i];

    return *this;
}

template <class Real>
Quaternion<Real>& Quaternion<Real>::operator*= (Real scalar)
{
    for (int i = 0; i < 4; ++i)
        components[i] *= scalar;

    return *this;
}

template <class Real>
Quaternion<Real>& Quaternion<Real>::operator/= (Real scalar)
{
    assert(abs(scalar) > EPSILON && "Quaternion: scalar divider equal or near zero");
    Real invScalar = 1.0f / scalar;
    for (i = 0; i < 4; ++i)
        components[i] *= invScalar;

    return *this;
}

template <class Real>
inline ostream& operator<<(ostream& outputStream, const Quaternion<Real>& quaternion)
{
    outputStream << setprecision(3) 
                 << "[ " << setw( 3 ) 
                 << quaternion.components[0] << ", " 
                 << quaternion.components[1] << ", " 
                 << quaternion.components[2] << ", "
                 << quaternion.components[3]
                 << " ]" << setw(0);
    return outputStream;
}

//
/// Useful function
//

template <class Real>
Real Quaternion<Real>::magnitude() const
{
    return sqrt(components[0] * components[0] +
                components[1] * components[1] +
                components[2] * components[2] +
                components[3] * components[3]);
}

template <class Real>
Real Quaternion<Real>::length() const
{
    return components[0] * components[0] +
           components[1] * components[1] +
           components[2] * components[2] +
           components[3] * components[3];
}

template <class Real>
Real Quaternion<Real>::dot(const Quaternion& rightSide) const
{
    Real dot = 0.0f;
    for (int i = 0; i < 4; ++i)
        dot += components[i] * rightSide.components[i];

    return dot;
}

template <class Real>
Real Quaternion<Real>::normalize()
{
    Real magn = magnitude();
    if (magn >= 0.0f)
    {
        Real invMagnitude = 1.0f / magn;
        components[0] *= invMagnitude;
        components[1] *= invMagnitude;
        components[2] *= invMagnitude;
        components[3] *= invMagnitude;
    }

    return magn;
}

template <class Real>
Quaternion<Real> Quaternion<Real>::inverse() const
{
    Quaternion inverse;

    Real norm = 0.0f;
    for (int i = 0; i < 4; ++i)
        norm += components[i] * components[i];

    if (norm > 0.0f)
    {
        Real invNorm = 1.0f / norm;
        inverse.components[0] = components[0]  * invNorm;
        inverse.components[1] = -components[1] * invNorm;
        inverse.components[2] = -components[2] * invNorm;
        inverse.components[3] = -components[3] * invNorm;
    }

    return inverse;
}

template <class Real>
Quaternion<Real> Quaternion<Real>::conjugate() const
{
    return Quaternion(components[0], -components[1], -components[2], -components[3]);
}

template <class Real>
void Quaternion<Real>::fromAxisAngle(Real angle, const Vector3<Real>& axis)
{
    Real halfAngle = angle * 0.5f;
    Vector3<Real> result = sin(halfAngle) * axis.normalize();
    components[0] = cos(halfAngle);
    components[1] = result.x();
    components[2] = result.y();
    components[3] = result.z();
}

template <class Real>
void Quaternion<Real>::fromAxisAngle(Real angle, const Vector4<Real>& axis)
{
    Real halfAngle = angle * 0.5f;
    Vector4<Real> result = sin(halfAngle) * axis.normalize();
    components[0] = cos(halfAngle);
    components[1] = result.x();
    components[2] = result.y();
    components[3] = result.z();
}

template <class Real>
void Quaternion<Real>::toRotationMatrix(Matrix3<Real>& matrix) const
{
    Real Tx  = 2.0f * components[1];
    Real Ty  = 2.0f * components[2];
    Real Tz  = 2.0f * components[3];
    Real Twx = Tx * components[0];
    Real Twy = Ty * components[0];
    Real Twz = Tz * components[0];
    Real Txx = Tx * components[1];
    Real Txy = Ty * components[1];
    Real Txz = Tz * components[1];
    Real Tyy = Ty * components[2];
    Real Tyz = Tz * components[2];
    Real Tzz = Tz * components[3];

    matrix(0, 0) = 1.0f - (Tyy + Tzz);
    matrix(0, 1) = Txy - Twz;
    matrix(0, 2) = Txz + Twy;
    matrix(1, 0) = Txy + Twz;
    matrix(1, 1) = 1.0f - (Txx + Tzz);
    matrix(1, 2) = Tyz - Twx;
    matrix(2, 0) = Txz - Twy;
    matrix(2, 1) = Tyz + Twx;
    matrix(2, 2) = 1.0f - (Txx + Tyy);
}

template <class Real>
void Quaternion<Real>::toAxisAngle(Real& angle, Vector3<Real>& axis) const
{
    // The quaternion representing the rotation is q = cos(theta/2) + sin(theta/2) * (x*i + y*j + z*k)
    Real length = components[0] * components[0] +
                  components[1] * components[1] +
                  components[2] * components[2] +
                  components[3] * components[3];

    if (length > EPSILON)
    {
        angle = 2.0f * acos(components[0]);
        Real invMagnitude = 1.0f / sqrt(length);
        axis[0] = components[1] * invMagnitude;
        axis[1] = components[2] * invMagnitude;
        axis[2] = components[3] * invMagnitude;
    }
    else
    {
        // angle is 0 (mod 2 * pi), so any axis will do
        angle = 0.0f;
        axis[0] = 1.0f;
        axis[1] = 0.0f;
        axis[2] = 0.0f;
    }
}

template <class Real>
void Quaternion<Real>::toAxisAngle(Real& angle, Vector4<Real>& axis) const
{
    // The quaternion representing the rotation is q = cos(theta/2) + sin(theta/2) * (x*i + y*j + z*k)
    Real length = components[0] * components[0] +
                  components[1] * components[1] +
                  components[2] * components[2] +
                  components[3] * components[3];

    if (length > EPSILON)
    {
        angle = 2.0f * acos(components[0]);
        Real invMagnitude = 1.0f / sqrt(length);
        axis[0] = components[1] * invMagnitude;
        axis[1] = components[2] * invMagnitude;
        axis[2] = components[3] * invMagnitude;
    }
    else
    {
        // angle is 0 (mod 2 * pi), so any axis will do
        angle = 0.0f;
        axis[0] = 1.0f;
        axis[1] = 0.0f;
        axis[2] = 0.0f;
    }
}