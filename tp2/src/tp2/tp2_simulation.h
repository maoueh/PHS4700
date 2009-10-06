#ifndef TP2_SIMULATION_H
#define TP2_SIMULATION_H

#include <vector>

#include "color.h"
#include "ode_euler.h"
#include "ode_runge_kutta4.h"
#include "opengl_application.h"

class ShaderProgram;
class TextureUnit;
class Window;

class Tp2Simulation : public OpenGlApplication
{
public:
    Tp2Simulation(CommandLine* commandLine, const Vector4d& initialPosition, const Vector4d& initialVelocity);
    virtual ~Tp2Simulation();

protected:
    virtual void    initialize();
    virtual STRING& getName() { return mName; }

    virtual void    keyPressed(KeyEvent& event);
    virtual void    mouseDragged(MouseEvent& event);

    virtual void    draw();

    virtual void    updateWorld();

private:
    static void positionOdeFunction(DOUBLE t, DOUBLE* lastPosition, DOUBLE* newPosition); // 3D
    static void linearVelocityOdeFunction(DOUBLE t, DOUBLE* lastLinearVelocity, DOUBLE* newLinearVelocity); // 3D
    static void rotationOdeFunction(DOUBLE t, DOUBLE* lastRotation, DOUBLE* newRotation); // 4D

    void compileHalfSoccerFieldList();
    void compileSoccerBallList();
    void drawQuadGrid(DOUBLE width, DOUBLE length, INT rowCount, INT columnCount, BOOL isOutsideNormal);
    void drawSphereQuarter(const Vector4d quarter, const Color& color);

    void replay();

    void checkEndOfSimulation();
    void checkFloor();
    void checkFieldAndGoal();
    void checkLeftAndRightFieldSide();
    void checkBackAndFrontFieldSide();
    void checkGoal(const Vector4d& estimatedPosition);

	void printHeader(const CHAR* title);
    void printResult(const Vector4d& estimatedPosition);

    static Vector4d sLinearVelocity;
    static Vector4d sAngularVelocity; 
    static Quaterniond sVelocityRotation;

    STRING mName;
    ShaderProgram* mShaderProgram;
    BOOL mIsShaderOn;

    OdeSolverd* mPositionOdeSolver;
    OdeSolverd* mLinearVelocityOdeSolver;
    OdeSolverd* mRotationOdeSolver;

    Vector4d mBallPosition;
    Vector4d mBallLinearVelocity;
    Vector4d mBallAngularVelocity;
    Quaterniond mBallRotation;
    DOUBLE mTimeElapsed;

    Vector4d mInitialLinearVelocity;
    Vector4d mInitialAngularVelocity;

    UINT mHalfSoccerFieldListId;
    UINT mSoccerBallListId;

    vector<Vector4d> mBallPositions;
    vector<Vector4d> mBallLinearVelocities;
    vector<Vector4d> mBallAngularVelocities;
    vector<Quaterniond> mBallRotations;

    DOUBLE mAxisScaleFactor;
    BOOL mIsAxisPresent;

    BOOL mIsGoalCrossed;
    BOOL mIsFloorCrossed;
    BOOL mIsSoccerFieldCrossed;
};

#endif