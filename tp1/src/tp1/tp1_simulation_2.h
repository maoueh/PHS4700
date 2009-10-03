#ifndef TP1_SIMULATION_2_H
#define TP1_SIMULATION_2_H

#include <vector>

#include "color.h"
#include "ode_euler.h"
#include "ode_runge_kutta4.h"
#include "opengl_application.h"

class ShaderProgram;
class TextureUnit;
class Window;

class Tp1Simulation2 : public OpenGlApplication
{
public:
    Tp1Simulation2(CommandLine* commandLine, const Vector& initialPosition, const Vector& initialVelocity);
    virtual ~Tp1Simulation2();

protected:
    virtual void    initialize();
    virtual STRING& getName() { return mName; }

    virtual void    keyPressed(KeyEvent& event);
    virtual void    mouseDragged(MouseEvent& event);

    virtual void    draw();

    virtual void    updateWorld();

private:
    static Vector4d sLastVelocity;

    void compileCourtList(FLOAT width, FLOAT length, INT rowCount, INT columnCount, BOOL isOutsideNormal);
    void compileNetList(FLOAT width, FLOAT length, INT rowCount, INT columnCount, BOOL isOutsideNormal);
    void drawQuadGrid(FLOAT width, FLOAT length, INT rowCount, INT columnCount, BOOL isOutsideNormal);

    void replay();

    void checkEndOfSimulation();
    void checkNet();
    void checkFloor();
    BOOL inPlayerOneZone();
    BOOL inPlayerTwoZone();
    void printBallOutside();
    void printResult();

    STRING mName;
    ShaderProgram* mShaderProgram;
    BOOL mIsShaderOn;

    static DOUBLE positionOdeFunction(DOUBLE t, DOUBLE lastPosition, INT i);
    static DOUBLE velocityOdeFunction(DOUBLE t, DOUBLE lastVelocity, INT i);

    OdeSolverd* mPositionOdeSolver;
    OdeSolverd* mVelocityOdeSolver;

    Vector4d mBallPosition;
    FLOAT mTimeElapsed;

    Vector mInitialPosition;
    Vector mInitialVelocity;

    UINT mCourtListId;
    UINT mNetListId;

    vector<Vector4d> mBallPositions;

    FLOAT mAxisScaleFactor;
    BOOL mIsAxisPresent;

    BOOL mIsNetCrossed;
};

#endif