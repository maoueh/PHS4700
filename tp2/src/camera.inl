
inline DOUBLE Camera::getRho() const
{
    return mRho;
}

inline DOUBLE Camera::getPhi() const
{
    return mPhi;
}

inline DOUBLE Camera::getTheta() const
{
    return mTheta;
}

inline const Vector3d& Camera::getPosition() const
{
    return mPosition;
}

inline const Vector3d& Camera::getTarget() const
{
    return mTarget;
}

inline const Vector3d& Camera::getUp() const
{
    return mUp;
}

inline const Vector3d& Camera::getRight() const
{
    return mRight;
}

inline Vector3d Camera::getDirection() const
{
    return mTarget - mPosition;
}

inline void Camera::setSpherical(DOUBLE rho, DOUBLE phi, DOUBLE theta)
{
    mRho = rho;
    mPhi = phi;
    mTheta = theta;
}

inline void Camera::setPosition(const Vector3d& position)
{
    mPosition = position;
}

inline void Camera::setTarget(const Vector3d& target)
{
    mTarget = target;
}

inline void Camera::setRho(DOUBLE rho)
{
    mRho = rho;
}

inline void Camera::setPhi(DOUBLE phi)
{
    mPhi = phi;
}

inline void Camera::setTheta(DOUBLE theta)
{
    mTheta = theta;
}