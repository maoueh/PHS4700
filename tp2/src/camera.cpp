#include "camera.h"

Camera::Camera() : 
    mRho(10.0f),           mTheta(0.0f),             mPhi(0.0f),
    mUp(0.0f, 0.0f, 1.0f), mRight(1.0f, 0.0f, 0.0f), mTarget(0.0f, 0.0f, 0.0f)
{
    update();
}

/// Parameters in radians
Camera::Camera(DOUBLE rho, DOUBLE phi, DOUBLE theta) : 
    mRho(rho),             mTheta(theta),            mPhi(phi),
    mUp(0.0f, 0.0f, 1.0f), mRight(1.0f, 0.0f, 0.0f), mTarget(0.0f, 0.0f, 0.0f)
{
    update();
}

Camera::~Camera()
{
    
}

void Camera::stepLeft()
{
    mTarget.y() += 2.0f;
}

void Camera::stepRight()
{
    mTarget.y() -= 2.0f;
}

void Camera::stepFoward()
{
    mTarget.x() += 2.0f;
}

void Camera::stepBackward()
{
    mTarget.x() -= 2.0f;
}

void Camera::update()
{
   mPosition.x() = mTarget.x() + (mRho * cos(mTheta) * sin(mPhi));
   mPosition.y() = mTarget.y() + (mRho * sin(mTheta) * sin(mPhi));
   mPosition.z() = mTarget.z() + (mRho * cos(mPhi));
}

// Negative delta to zoom in, positive to zoom out
void Camera::zoom(DOUBLE delta)
{
    mRho += delta;
    if (mRho <= 1.0f)
        mRho = 1.0f;
}

// Accept negative delta to work has expected
void Camera::zoomIn(DOUBLE delta)
{
    zoom(-delta);
}

// Accept positive delta to work has expected
void Camera::zoomOut(DOUBLE delta)
{
    zoom(delta);
}