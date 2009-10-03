#include "tp1_simulation_1.h"
#include "tp1_constants.h"
#include "tp1_shader_program.h"

#include "color.h"
#include "null_logger.h"
#include "texture_unit.h"
#include "window.h"

Tp1Simulation1::Tp1Simulation1(CommandLine* commandLine, 
                               const Vector& initialPosition, 
                               const Vector& initialVelocity) : OpenGlApplication(commandLine),
    mName("Tp1 - PHS4700 (Simulation #1)"),  mIsShaderOn(FALSE),              
    mAxisScaleFactor(15.0f),                 mIsAxisPresent(TRUE),
    mInitialPosition(initialPosition),       mInitialVelocity(initialVelocity), 
    mBallPosition(initialPosition),          mBallVelocity(initialVelocity),
    mTimeElapsed(0.0f),                      mIsNetCrossed(FALSE)
{
    mBallPositions.push_back(mBallPosition);

    delete mLogger;
    mLogger = new NullLogger();
}

Tp1Simulation1::~Tp1Simulation1()
{
}

void Tp1Simulation1::initialize()
{
    OpenGlApplication::initialize();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Separate calculation of the specular contribution after texturing is done
    glLightModeli( GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR ); 
    glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE ); 
    glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE ); // Two-side mode in OpenGL
    glEnable( GL_VERTEX_PROGRAM_TWO_SIDE );            // Two-side mode in GLSL            

    // Compile Display List
    compileCourtList(Tp1Constants::COURT_WIDTH, Tp1Constants::COURT_LENGTH, 4, 1, TRUE);
    compileNetList(Tp1Constants::COURT_WIDTH, Tp1Constants::NET_HEIGHT, 1, 1, TRUE);

    // The Vertex and Fragment Shaders are initialized in the constructor
    mShaderProgram = new Tp1ShaderProgram();
    mShaderProgram->link();
}

void Tp1Simulation1::compileCourtList(FLOAT width, FLOAT length, INT rowCount, INT columnCount, BOOL isOutsideNormal)
{
    mCourtListId = glGenLists(1);
    glNewList(mCourtListId, GL_COMPILE);
    {
        drawQuadGrid(width, length, rowCount, columnCount, isOutsideNormal);
    }
    glEndList();
}

void Tp1Simulation1::compileNetList(FLOAT width, FLOAT length, INT rowCount, INT columnCount, BOOL isOutsideNormal)
{
    mNetListId = glGenLists(1);
    glNewList(mNetListId, GL_COMPILE);
    {
        drawQuadGrid(width, length, rowCount, columnCount, isOutsideNormal);
    }
    glEndList();
}

void Tp1Simulation1::drawQuadGrid(FLOAT width, FLOAT length, INT rowCount, INT columnCount, BOOL isOutsideNormal) 
{
   INT normFact = isOutsideNormal ? 1 : -1;
   
   FLOAT startX = 0;
   FLOAT startY = 0;
   FLOAT incrementX = width / (FLOAT) columnCount;
   FLOAT incrementY = length / (FLOAT) rowCount;

   glBegin(GL_QUADS);
   glNormal3f(0.0f, (FLOAT) normFact, 0.0f);

   for ( INT i = 0; i < columnCount; ++i )
   {
      for ( INT k = 0; k < rowCount; ++k )
      {
         glVertex3f(startX + i * incrementX, startY + k * incrementY, 0.0f);
         glVertex3f((startX + i * incrementX) + incrementX, startY + k * incrementY, 0.0f);
         glVertex3f((startX + i * incrementX) + incrementX, (startY + k * incrementY) + incrementY, 0.0f);
         glVertex3f(startX + i * incrementX, (startY + k * incrementY) + incrementY, 0.0f);
      }
   }
   glEnd();
}

void Tp1Simulation1::keyPressed(KeyEvent& event)
{
   switch(event.keyCode) 
   {
      case VK_X :
           mIsShaderOn = !mIsShaderOn;
           break;
      case VK_A :
          mIsAxisPresent = !mIsAxisPresent;              // Toggle Axis Presence
          break;
      case VK_R :
          replay();
          break;
	}

    OpenGlApplication::keyPressed(event);
}

void Tp1Simulation1::mouseDragged(MouseEvent& event)
{
    FLOAT mDeltaX = (event.x - event.lastX) / (FLOAT) mWindow->getWidth();
    FLOAT mDeltaY = (event.y - event.lastY) / (FLOAT) mWindow->getHeight();
    
    mCameraTheta += DEG2RAD(360.0f * mDeltaX * Tp1Constants::CAMERA_THETA_ROTATION_SPEED);
    if ( mCameraTheta > DOUBLE_PI )  mCameraTheta -= DOUBLE_PI;
    if ( mCameraTheta < -DOUBLE_PI ) mCameraTheta += DOUBLE_PI;
    
    mCameraPhi += DEG2RAD(180.0f * mDeltaY * Tp1Constants::CAMERA_PHI_ROTATION_SPEED);
    if ( mCameraPhi > HALF_PI )  mCameraPhi = HALF_PI;
    if ( mCameraPhi < -PI ) mCameraPhi = -PI;
}

void Tp1Simulation1::replay()
{
    mTimeElapsed = 0.0f;
    mBallPosition = mInitialPosition;
    mIsNetCrossed = FALSE;

    mBallPositions.clear();
    mBallPositions.push_back(mBallPosition);
}

void Tp1Simulation1::draw()
{
    if ( mIsShaderOn )
        mShaderProgram->use();
    else
        glUseProgram(EMPTY_SHADER_PROGRAM);

    glDisable(GL_FOG);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    glTranslatef(-2.5f, -10.0f, 0.0f);

    glColor4fv(Color::WHITE.components);
    glCallList(mCourtListId);

    glPushMatrix();
    {
        glTranslatef(0.0f, Tp1Constants::COURT_LENGTH / 2.0f, 0.0f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glCallList(mNetListId);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glBegin(GL_POINTS);
        {
            for (UINT i = 0; i < mBallPositions.size(); ++i)
                glVertex3fv(mBallPositions[i].components);
        }
        glEnd();
    }
    glPopMatrix();

    if ( mIsAxisPresent )
    {
        glUseProgram(EMPTY_SHADER_PROGRAM); 
        glPushMatrix();
        {		    	
            glTranslatef(-0.5f, -0.5f, 0.0f);

            glLineWidth(1.5);

            glBegin(GL_LINES);
            {
                // X axis in red
                glColor4f(1.0, 0.0, 0.0, 1.0);
                glVertex3f(0.0, 0.0, 0.0);
                glVertex3f(1.0f * mAxisScaleFactor, 0.0, 0.0);

                // Y axis in green
                glColor4f(0.0, 1.0, 0.0, 1.0);
                glVertex3f(0.0, 0.0, 0.0);
                glVertex3f(0.0, 1.0f * mAxisScaleFactor, 0.0);

                // Z axis in blue
                glColor4f(0.0, 0.0, 1.0, 1.0);
                glVertex3f(0.0, 0.0, 0.0);
                glVertex3f(0.0, 0.0, 1.0f * mAxisScaleFactor);
            }
            glEnd();

            glEnable(GL_LIGHTING);
        }
        glPopMatrix();

        if ( mIsShaderOn )
            mShaderProgram->use();
        else
            glUseProgram(EMPTY_SHADER_PROGRAM);
    }

    glFlush();
}

void Tp1Simulation1::updateWorld()
{
    if ( mBallPosition.z() <= 0 )
        return;

    /// x(t) = x0 + v0 * t + ag * (t^2 / 2)
    //  ag                 = Gravity

    /// positionPart       = x0
    /// velocityPart       = v0 * t
    /// accelerationScalar = t^2 / 2
    /// accelerationPart   = ag * accelerationScalar
    /// x(t)               = positionPart + velocityPart + accelerationPart

    Vector positionPart = mInitialPosition;
    Vector velocityPart = mInitialVelocity * (FLOAT) mTimeElapsed;

    FLOAT accelerationScalar = (mTimeElapsed * mTimeElapsed) / 2.0f;
    Vector accelerationPart = Tp1Constants::GRAVITY * accelerationScalar;

    mBallPosition = positionPart + velocityPart + accelerationPart;
    mBallPositions.push_back(mBallPosition);

    mBallVelocity = mInitialVelocity + Tp1Constants::GRAVITY * mTimeElapsed;

    mTimeElapsed += Tp1Constants::SIMULATION_1_TIME_STEP;

    checkEndOfSimulation();
}

void Tp1Simulation1::checkEndOfSimulation()
{
    checkFloor();
    checkNet();
}

// Check to see if the ball overcome the net
void Tp1Simulation1::checkNet()
{
    // Do nothing if the net has already been crossed
    if ( mIsNetCrossed )
        return;

    // Since we know that the net is not crossed yet, the first y > zone_length indicate crossing of net
    if ( mBallPosition.y() >= Tp1Constants::PLAYER_ZONE_LENGTH )
    {
        mIsNetCrossed = TRUE;

        // The net is between this position and the last one so we try to interpolate the z
        // if the position is within the limit of the court
        if ( mBallPosition.x() >= 0.0f && mBallPosition.x() <= Tp1Constants::COURT_WIDTH )
        {
            // The very last is == mBallPosition so the one before mBallPosition is size() - 2
            Vector lastBallPosition = mBallPositions[mBallPositions.size() - 2];
            FLOAT deltaY = mBallPosition.y() - lastBallPosition.y();
            FLOAT deltaZ = mBallPosition.z() - lastBallPosition.z();
            FLOAT ratioY = abs(mBallPosition.y() - Tp1Constants::PLAYER_ZONE_LENGTH) / deltaY;

            FLOAT estimatedZ = mBallPosition.z() + deltaZ * ratioY;

            if ( estimatedZ <= Tp1Constants::NET_HEIGHT )
            {
                cout << "================== Resultats ================== " << endl;
                cout << "  La balle ne traverse pas le filet (Echec)" << endl << endl;
                printResult();

                mBallPosition.z() = 0.0f; // This will stop the simulation at the next step
            }
        }
    }
}

// Check to see if the ball hit the floor
void Tp1Simulation1::checkFloor()
{
    if ( mBallPosition.z() < 0.0f )
    {
        cout << "================== Resultats ================== " << endl;
        if ( inPlayerOneZone() )
            cout << "  La balle a atterie dans la zone du joueur #1 (Echec)" << endl;
        else if ( inPlayerTwoZone() )
            cout << "  La balle a atterie dans la zone du joueur #2 (Succes)" << endl;
        else
            printBallOutside();

        cout << endl;
        printResult();
    }
}

void Tp1Simulation1::printBallOutside()
{
    if ( mBallPosition.y() >= Tp1Constants::COURT_LENGTH )
        cout << "  La balle a atterie au fond du court (Echec)" << endl;
    else if ( mBallPosition.x() < 0.0 )
        cout << "  La balle a atterie a gauche du court (Echec)" << endl;
    else
        cout << "  La balle a atterie a droite du court (Echec)" << endl;
}

BOOL Tp1Simulation1::inPlayerOneZone() // My zone (or start zone)
{
    return mBallPosition.x() >= 0.0f && mBallPosition.x() <= Tp1Constants::COURT_WIDTH &&
           mBallPosition.y() >= 0.0f && mBallPosition.y() <= Tp1Constants::PLAYER_ZONE_LENGTH;
}

BOOL Tp1Simulation1::inPlayerTwoZone() // Zone of the opponent
{
    return mBallPosition.x() >= 0.0f && mBallPosition.x() <= Tp1Constants::COURT_WIDTH &&
           mBallPosition.y() > Tp1Constants::PLAYER_ZONE_LENGTH && mBallPosition.y() <= Tp1Constants::COURT_LENGTH;
}

void Tp1Simulation1::printResult()
{
    cout << "Position Finale     : " << mBallPosition << " metres" << endl;
    cout << "Vitesse  Finale     : " << mBallVelocity << " metres/seconde" << endl;
    cout << "Nombre d'iterations : " << mBallPositions.size() << endl;
    cout << "Temps Ecoule        : " << setprecision(3) << mTimeElapsed << " secondes" << endl << endl;
    cout << "===================== Fin ===================== " << endl << endl;
}