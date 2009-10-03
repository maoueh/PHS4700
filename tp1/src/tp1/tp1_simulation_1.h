#ifndef TP1_SIMULATION_1_H
#define TP1_SIMULATION_1_H

#include <vector>

#include "color.h"
#include "opengl_application.h"

class ShaderProgram;
class TextureUnit;
class Window;

class Tp1Simulation1 : public OpenGlApplication
{
public:
    Tp1Simulation1(CommandLine* commandLine, const Vector& initialPosition, const Vector& initialVelocity);
    virtual ~Tp1Simulation1();

protected:
    virtual void    initialize();
    virtual STRING& getName() { return mName; }

    virtual void    keyPressed(KeyEvent& event);
    virtual void    mouseDragged(MouseEvent& event);

    virtual void    draw();

    virtual void    updateWorld();

private:
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

    Vector mBallVelocity;
    Vector mBallPosition;
    FLOAT mTimeElapsed;

    Vector mInitialPosition;
    Vector mInitialVelocity;

    UINT mCourtListId;
    UINT mNetListId;

    vector<Vector> mBallPositions;

    FLOAT mAxisScaleFactor;
    BOOL mIsAxisPresent;

    BOOL mIsNetCrossed;
};

#endif