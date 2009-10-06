
template <typename Real>
Vector3<Real> MathUtils<Real>::interpolate3(const Vector3<Real>& v1, const Vector3<Real>& v2, 
                                            Real valueLookedFor, INT deltaComponent)
{
    Vector3<Real> delta = v2 - v1;
    const Real ratio = abs((v1[deltaComponent] - valueLookedFor) / delta[deltaComponent]);

    return v1 + delta * ratio;
}

template <typename Real>
Vector4<Real> MathUtils<Real>::interpolate4(const Vector4<Real>& v1, const Vector4<Real>& v2, 
                                            Real valueLookedFor, INT deltaComponent)
{
    Vector4<Real> delta = v2 - v1;
    const Real ratio = abs((v1[deltaComponent] - valueLookedFor) / delta[deltaComponent]);

    return v1 + delta * ratio;
}