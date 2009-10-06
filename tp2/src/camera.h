#ifndef GAME_ENGINE_CAMERA_H
#define GAME_ENGINE_CAMERA_H

#include "common.h"
#include "vector3.h"

class Camera
{

public:
    Camera();
    /// Parameters in radians
    Camera(DOUBLE rho, DOUBLE phi, DOUBLE theta);
    virtual ~Camera();

    inline DOUBLE getRho() const;
    inline DOUBLE getPhi() const;
    inline DOUBLE getTheta() const;

    inline const Vector3d& getPosition() const;
    inline const Vector3d& getTarget() const;
    inline const Vector3d& getUp() const;
    inline const Vector3d& getRight() const;

    inline Vector3d getDirection() const;

    inline void setSpherical(DOUBLE rho, DOUBLE phi, DOUBLE theta);

    inline void setRho(DOUBLE rho);
    inline void setPhi(DOUBLE phi);
    inline void setTheta(DOUBLE theta);

    inline void setPosition(const Vector3d& position);
    inline void setTarget(const Vector3d& target);

    virtual void stepLeft();
    virtual void stepRight();
    virtual void stepFoward();
    virtual void stepBackward();

    virtual void update();

    // Negative delta to zoom in, positive to zoom out
    virtual void zoom(DOUBLE delta);
    // Accept negative delta to work has expected
    virtual void zoomIn(DOUBLE delta);
    // Accept positive delta to work has expected
    virtual void zoomOut(DOUBLE delta);

protected:
    DOUBLE mTheta;
    DOUBLE mRho;
    DOUBLE mPhi;
    
    Vector3d mPosition;
    Vector3d mTarget;
    Vector3d mUp;
    Vector3d mRight;

};

#include "camera.inl"

#endif