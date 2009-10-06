#include "tp2_simulation.h"
#include "tp2_constants.h"
#include "tp2_shader_program.h"

#include "color.h"
#include "math_utils.h"
#include "null_logger.h"
#include "window.h"

Vector4d Tp2Simulation::sLinearVelocity = Vector4d::ZERO;
Vector4d Tp2Simulation::sAngularVelocity = Vector4d::ZERO;
Quaterniond Tp2Simulation::sVelocityRotation = Quaterniond::ZERO;

Tp2Simulation::Tp2Simulation(CommandLine* commandLine, 
                             const Vector4d& initialLinearVelocity, 
                             const Vector4d& initialAngularVelocity) : OpenGlApplication(commandLine),
    mName("Tp2 - PHS4700"),                          mIsShaderOn(FALSE),              
    mAxisScaleFactor(15.0f),                         mIsAxisPresent(TRUE),
    mPositionOdeSolver(NULL),                        mRotationOdeSolver(NULL),
    mTimeElapsed(0.0f),                              mIsGoalCrossed(FALSE),
    mIsSoccerFieldCrossed(FALSE),                    mIsFloorCrossed(FALSE), 
    mInitialLinearVelocity(initialLinearVelocity),   mBallAngularVelocity(initialAngularVelocity),
    mInitialAngularVelocity(initialAngularVelocity), mBallLinearVelocity(initialLinearVelocity),
    mBallPosition(0.0f, 0.0f, 0.0f, 0.0f),           mBallRotation(1.0f, 0.0f, 0.0f, 0.0f)
{    
    sLinearVelocity = initialLinearVelocity;
    sAngularVelocity = initialAngularVelocity;
    sVelocityRotation.set(0.0f, 
                          initialAngularVelocity.x(),
                          initialAngularVelocity.y(),
                          initialAngularVelocity.z());
    mPositionOdeSolver = new OdeRungeKutta4d(mBallPosition.components, 3, positionOdeFunction,                                   
                                             Tp2Constants::SIMULATION_TIME_STEP);

    mLinearVelocityOdeSolver = new OdeRungeKutta4d(mBallLinearVelocity.components, 3, linearVelocityOdeFunction,                                   
                                             Tp2Constants::SIMULATION_TIME_STEP);

    mRotationOdeSolver = new OdeRungeKutta4d(mBallRotation.components, 4, rotationOdeFunction,                                   
                                             Tp2Constants::SIMULATION_TIME_STEP);

    mBallPositions.push_back(mBallPosition);
    mBallLinearVelocities.push_back(mBallLinearVelocity);
    mBallAngularVelocities.push_back(mBallAngularVelocity);
    mBallRotations.push_back(mBallRotation);

    mCamera->setSpherical(30.0f, DEG2RAD(45.0f), DEG2RAD(205.0f));

    delete mLogger;
    mLogger = new NullLogger();
}

Tp2Simulation::~Tp2Simulation()
{
}

void Tp2Simulation::initialize()
{
    OpenGlApplication::initialize();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Separate calculation of the specular contribution after texturing is done
    glLightModeli( GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR ); 
    glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE ); 
    glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE ); // Two-side mode in OpenGL
    glEnable( GL_VERTEX_PROGRAM_TWO_SIDE );            // Two-side mode in GLSL            

    // Compile Display List
    compileHalfSoccerFieldList();
    compileSoccerBallList();

    // The Vertex and Fragment Shaders are initialized in the constructor
    mShaderProgram = new Tp2ShaderProgram();
    mShaderProgram->link();
}

void Tp2Simulation::compileHalfSoccerFieldList()
{
    mHalfSoccerFieldListId = glGenLists(1);
    glNewList(mHalfSoccerFieldListId, GL_COMPILE);
    {
        glPushMatrix();
        {
            // Soccer Field
            drawQuadGrid(Tp2Constants::SOCCER_FIELD_WIDTH, Tp2Constants::SOCCER_FIELD_HALF_LENGTH, 1, 1, TRUE);

            // Penalty Box
            glPushMatrix();
            {
                glTranslated(Tp2Constants::PENALTY_BOX_OFFSET_X, 0.0f, 0.0f);
                drawQuadGrid(Tp2Constants::PENALTY_BOX_WIDTH, Tp2Constants::PENALTY_BOX_LENGTH, 1, 1, TRUE);
            }
            glPopMatrix();

            // Goal Box
            glPushMatrix();
            {
                glTranslated(Tp2Constants::GOAL_BOX_OFFSET_X, 0.0f, 0.0f);
                drawQuadGrid(Tp2Constants::GOAL_BOX_WIDTH, Tp2Constants::GOAL_BOX_LENGTH, 1, 1, TRUE);
            }
            glPopMatrix();

            // Goal
            glPushMatrix();
            {
                glTranslated(Tp2Constants::GOAL_OFFSET_X, Tp2Constants::GOAL_OFFSET_Y, 0.0f);
                drawQuadGrid(Tp2Constants::GOAL_WIDTH, Tp2Constants::GOAL_LENGTH, 1, 1, TRUE);
            }
            glPopMatrix();
        } 
        glPopMatrix();
    }
    glEndList();
}

void Tp2Simulation::compileSoccerBallList()
{
    Vector4d quarters[] = { Tp2Constants::QUARTER_1, Tp2Constants::QUARTER_2, 
                            Tp2Constants::QUARTER_3, Tp2Constants::QUARTER_4, 
                            Tp2Constants::QUARTER_5, Tp2Constants::QUARTER_6,
                            Tp2Constants::QUARTER_7, Tp2Constants::QUARTER_8 };

    Color colors[] = { Color::RED,    Color::GREEN, 
                       Color::YELLOW, Color::BLUE, 
                       Color::BLUE,   Color::YELLOW,
                       Color::GREEN,  Color::RED };

    mSoccerBallListId = glGenLists(1);
    glNewList(mSoccerBallListId, GL_COMPILE);
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glPushMatrix();
        {
            for(INT i = 0; i < Tp2Constants::QUARTER_COUNT; ++i)
                drawSphereQuarter(quarters[i], colors[i]);
        }
        glPopMatrix();
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    glEndList();
}

void Tp2Simulation::drawQuadGrid(DOUBLE width, DOUBLE length, INT rowCount, INT columnCount, BOOL isOutsideNormal) 
{
   INT normFact = isOutsideNormal ? 1 : -1;
   
   DOUBLE startX = 0;
   DOUBLE startY = 0;
   DOUBLE incrementX = width / (DOUBLE) columnCount;
   DOUBLE incrementY = length / (DOUBLE) rowCount;

   glBegin(GL_QUADS);
   glNormal3d(0.0f, (DOUBLE) normFact, 0.0f);

   for ( INT i = 0; i < columnCount; ++i )
   {
      for ( INT k = 0; k < rowCount; ++k )
      {
         glVertex3d(startX + i * incrementX, startY + k * incrementY, 0.0f);
         glVertex3d((startX + i * incrementX) + incrementX, startY + k * incrementY, 0.0f);
         glVertex3d((startX + i * incrementX) + incrementX, (startY + k * incrementY) + incrementY, 0.0f);
         glVertex3d(startX + i * incrementX, (startY + k * incrementY) + incrementY, 0.0f);
      }
   }
   glEnd();
}

void Tp2Simulation::drawSphereQuarter(const Vector4d quarter, const Color& color) 
{
   DOUBLE r = Tp2Constants::SOCCER_BALL_RADIUS;
   DOUBLE qx = quarter.x(); DOUBLE qy = quarter.y(); DOUBLE qz = quarter.z();
   DOUBLE cos00 = 1.0;
   DOUBLE sin00 = 0.0;
   DOUBLE cos45 = cos(DEG2RAD(45));
   DOUBLE sin45 = sin(DEG2RAD(45));
   DOUBLE sin90 = 1.0;
   DOUBLE cos90 = 0.0;

   glColor4fv(color.components);
   glBegin(GL_TRIANGLE_FAN);
   {
       // The qx, qy, qz are either 1 or -1, it decides to which quarter the coordinate belong
       glVertex3d( qx * r * cos45 * sin45, qy * r * sin45 * sin45, qz * r * cos45 ); // Middle Point of the quarter
       glVertex3d( qx * r * cos00 * sin00, qy * r * sin00 * sin00, qz * r * cos00 ); // Top point of the quarter
       glVertex3d( qx * r * cos00 * sin45, qy * r * sin00 * sin45, qz * r * cos45 ); 
       glVertex3d( qx * r * cos00 * sin90, qy * r * sin00 * sin90, qz * r * cos90 );
       glVertex3d( qx * r * cos45 * sin90, qy * r * sin45 * sin90, qz * r * cos90 );
       glVertex3d( qx * r * cos90 * sin90, qy * r * sin90 * sin90, qz * r * cos90 );
       glVertex3d( qx * r * cos90 * sin45, qy * r * sin90 * sin45, qz * r * cos45 );
       glVertex3d( qx * r * cos00 * sin00, qy * r * sin00 * sin00, qz * r * cos00 ); // Top point of the quarter
   }
   glEnd();
}


void Tp2Simulation::keyPressed(KeyEvent& event)
{
   switch(event.keyCode) 
   {
      case VK_X :
           mIsShaderOn = !mIsShaderOn;
           break;
      case VK_A :
          mIsAxisPresent = !mIsAxisPresent;              // Toggle Axis Presence
          break;
      case VK_D :
          cout << "Theta (" << RAD2DEG(mCamera->getTheta()) 
               << ") Phi (" << RAD2DEG(mCamera->getPhi()) 
               << ") Rho (" << mCamera->getRho() << ")\n";
          break;
      case VK_R :
          replay();
          break;
	}

    OpenGlApplication::keyPressed(event);
}

void Tp2Simulation::mouseDragged(MouseEvent& event)
{
    FLOAT mDeltaX = (event.x - event.lastX) / (FLOAT) mWindow->getWidth();
    FLOAT mDeltaY = (event.y - event.lastY) / (FLOAT) mWindow->getHeight();

    DOUBLE theta = mCamera->getTheta();
    DOUBLE phi = mCamera->getPhi();

    theta += (FLOAT) DEG2RAD(360.0f * mDeltaX * Tp2Constants::CAMERA_THETA_ROTATION_SPEED);
    if ( theta > DOUBLE_PI )  theta -= DOUBLE_PI;
    if ( theta < -DOUBLE_PI ) theta += DOUBLE_PI;
    
    phi += (FLOAT) DEG2RAD(180.0f * mDeltaY * Tp2Constants::CAMERA_PHI_ROTATION_SPEED);
    if ( phi > HALF_PI )  phi = HALF_PI;
    if ( phi < -PI ) phi = -PI;

    mCamera->setTheta(theta);
    mCamera->setPhi(phi);
}

void Tp2Simulation::replay()
{
    mTimeElapsed = 0.0f;
    //mBallPosition.set(mInitialPosition.x(), mInitialPosition.y(), mInitialPosition.z());
    mBallPosition.set(0.0f, 0.0f, 0.0f);
    mBallLinearVelocity = mInitialLinearVelocity;
    mBallRotation = Quaterniond(1.0f, 0.0f, 0.0f, 0.0f);

    mPositionOdeSolver->reset(mBallPosition);
    mLinearVelocityOdeSolver->reset(mBallLinearVelocity);
    mRotationOdeSolver->reset(mBallRotation);

    mIsGoalCrossed = FALSE;
    mIsFloorCrossed = FALSE;
    mIsSoccerFieldCrossed = FALSE;
    mBallPositions.clear();
    mBallPositions.push_back(mBallPosition);

    mBallRotations.clear();
    mBallRotations.push_back(mBallRotation);
}

void Tp2Simulation::draw()
{
    if ( mIsShaderOn )
        mShaderProgram->use();
    else
        glUseProgram(EMPTY_SHADER_PROGRAM);

    glDisable(GL_FOG);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    //glTranslatef(-2.5f, -10.0f, 0.0f);

    glColor4fv(Color::WHITE.components);
    glCallList(mHalfSoccerFieldListId);

    glPushMatrix();
    {
        glTranslated(0.0f, Tp2Constants::SOCCER_FIELD_LENGTH, 0.0f);
        glRotated(180.0f, 1.0f, 0.0f, 0.0f);
        glCallList(mHalfSoccerFieldListId);
    }
    glPopMatrix();

    DOUBLE angle; Vector3d axis;
    for(unsigned int i = 0; i < mBallPositions.size(); ++i)
    {
        glPushMatrix();
        {
            mBallRotations[i].toAxisAngle(angle, axis);

            glTranslated(mBallPositions[i].x(), mBallPositions[i].y(), mBallPositions[i].z());
            glRotated(RAD2DEG(angle), axis.x(), axis.y(), axis.z());

            glCallList(mSoccerBallListId);
        }
        glPopMatrix();
    }

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
                glVertex3d(1.0f * mAxisScaleFactor, 0.0, 0.0);

                // Y axis in green
                glColor4f(0.0, 1.0, 0.0, 1.0);
                glVertex3d(0.0, 0.0, 0.0);
                glVertex3d(0.0, 1.0f * mAxisScaleFactor, 0.0);

                // Z axis in blue
                glColor4f(0.0, 0.0, 1.0, 1.0);
                glVertex3d(0.0, 0.0, 0.0);
                glVertex3d(0.0, 0.0, 1.0f * mAxisScaleFactor);
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

void Tp2Simulation::updateWorld()
{
    // Stop updating if one this condition is true
    if ( mIsGoalCrossed || mIsFloorCrossed || mIsSoccerFieldCrossed )
        return;
   
    mTimeElapsed += Tp2Constants::SIMULATION_TIME_STEP;

    // Using Runge-Kutta's Fourth Order Method for the solver in this case
    // See ode_solver.h and ode_runge_kutta4.h in GameEngine project to see how it is implemented
    mBallLinearVelocity.set3(mLinearVelocityOdeSolver->step());
    sLinearVelocity = mBallLinearVelocity;

    mBallLinearVelocities.push_back(mBallLinearVelocity);

    mBallPosition.set3(mPositionOdeSolver->step());
    // The w component is used to store the time elapsed at this position
    // this will ease interpolation of position and time at the same time
    mBallPosition.w() = mTimeElapsed;
    mBallPositions.push_back(mBallPosition);

    mBallRotation.set(mRotationOdeSolver->step());
    mBallRotation.normalize();
    mBallRotations.push_back(mBallRotation);

    checkEndOfSimulation();
}

// Function for position ODE
void Tp2Simulation::positionOdeFunction(DOUBLE t, DOUBLE* lastPosition, DOUBLE* newPosition)
{
    for (int i = 0; i < 3; ++i)
        newPosition[i] = sLinearVelocity[i];
}

// Function for velocity ODE
void Tp2Simulation::linearVelocityOdeFunction(DOUBLE t, DOUBLE* lastLinearVelocity, DOUBLE* newLinearVelocity)
{
    Vector3d v(lastLinearVelocity);
    Vector3d w(sAngularVelocity.x(), sAngularVelocity.y(), sAngularVelocity.z()); 
    Vector3d VcrossW = Vector3d::crossProduct(w, v).normalize();
    const DOUBLE invMass = 1 / Tp2Constants::SOCCER_BALL_MASS;
    const DOUBLE m       = Tp2Constants::SOCCER_BALL_MASS;
    const DOUBLE r       = Tp2Constants::SOCCER_BALL_RADIUS;
    const DOUBLE p       = Tp2Constants::AIR_DENSITY;
    const DOUBLE A       = PI * r * r;
    const DOUBLE normV   = v.magnitude();
    const DOUBLE normW   = w.magnitude();
    const DOUBLE Cvis    = Tp2Constants::AIR_VISCOSITY;
    const DOUBLE Cm      = 0.385 * pow((normW * r) / normV, 0.25);

    Vector3d F1 = -p * Cvis * A * 0.5 * normV * v;
    Vector3d F2 = p * Cm * A * 0.5 * normV * normV * VcrossW;
    Vector3d F3 = m * Tp2Constants::GRAVITY; // The GRAVITY constant is (0, 0, -9.8)
    Vector3d result = invMass * (F1 + F2 + F3);

    result.assignTo(newLinearVelocity);
}

// Function for rotation ODE
void Tp2Simulation::rotationOdeFunction(DOUBLE t, DOUBLE* lastRotation, DOUBLE* newRotation)
{
    Quaterniond lastRot(lastRotation);
    Quaterniond result = (lastRot * sVelocityRotation) * 0.5f;

    result.assignTo(newRotation);
}

void Tp2Simulation::checkEndOfSimulation()
{
    checkFloor();
    checkFieldAndGoal();
}

// Check to see if the ball is in the field
void Tp2Simulation::checkFieldAndGoal()
{
    if ( mIsSoccerFieldCrossed || mIsFloorCrossed || mIsGoalCrossed )
        return;

    checkLeftAndRightFieldSide();
    checkBackAndFrontFieldSide(); // Will check if the ball is in the goal here
}

// Check to see if the ball is outside the left or right side
void Tp2Simulation::checkLeftAndRightFieldSide()
{
    if ( mBallPosition.x() < 0.0f )
    {
        Vector4d lastBallPosition = mBallPositions[mBallPositions.size() - 2];
        Vector4d estimatedPosition = MathUtils<DOUBLE>::interpolate4(lastBallPosition, mBallPosition, 
                                                                     0.0f, COMPONENT_X);

		printHeader("La balle a atterie a gauche du terrain (Echec)");
        printResult(estimatedPosition);
        mIsSoccerFieldCrossed = TRUE;
    }

    if ( mBallPosition.x() > Tp2Constants::SOCCER_FIELD_WIDTH )
    {
        Vector4d lastBallPosition = mBallPositions[mBallPositions.size() - 2];
        Vector4d estimatedPosition = MathUtils<DOUBLE>::interpolate4(lastBallPosition, mBallPosition, 
                                                                     Tp2Constants::SOCCER_FIELD_WIDTH, COMPONENT_X);

		printHeader("La balle a atterie a droite du terrain (Echec)");
        printResult(estimatedPosition);
        mIsSoccerFieldCrossed = TRUE;
    }
}

// Check to see if the ball is outside the left or right side
void Tp2Simulation::checkBackAndFrontFieldSide()
{
    if ( mBallPosition.y() < 0.0f )
    {
        Vector4d lastBallPosition = mBallPositions[mBallPositions.size() - 2];
        Vector4d estimatedPosition = MathUtils<DOUBLE>::interpolate4(lastBallPosition, mBallPosition, 
                                                                     0.0f, COMPONENT_Y);
        // Check if the ball is in the goal
        checkGoal(estimatedPosition);
        
        // If the ball didn't cross the goal, the ball is outside the field
        if ( !mIsGoalCrossed )
        {
			printHeader("La balle a atterie a l'arriere du terrain du terrain (Echec)");
            printResult(estimatedPosition);
            mIsSoccerFieldCrossed = TRUE;
        }
    }

    if ( mBallPosition.y() > Tp2Constants::SOCCER_FIELD_LENGTH )
    {
        Vector4d lastBallPosition = mBallPositions[mBallPositions.size() - 2];
        Vector4d estimatedPosition = MathUtils<DOUBLE>::interpolate4(lastBallPosition, mBallPosition, 
                                                                     Tp2Constants::SOCCER_FIELD_LENGTH, COMPONENT_Y);

		printHeader("La balle a atterie a l'avant du terrain (Echec)");
        printResult(estimatedPosition);
        mIsSoccerFieldCrossed = TRUE;
    }
}

// Check to see if the ball overcome the net
void Tp2Simulation::checkGoal(const Vector4d& estimatedPosition)
{
    // Do nothing if the net has already been crossed
    if ( mIsFloorCrossed || mIsGoalCrossed || mIsSoccerFieldCrossed )
        return;
    
    // Inside the goal
    if ( estimatedPosition.x() > Tp2Constants::GOAL_START_X && estimatedPosition.x() < Tp2Constants::GOAL_END_X && 
         estimatedPosition.z() > Tp2Constants::GOAL_START_Z && estimatedPosition.z() < Tp2Constants::GOAL_END_Z)
    {
		printHeader("La balle a atterie dans le but (Succes)");
        printResult(estimatedPosition);
        mIsGoalCrossed = TRUE; 
    }
    
}
//
//// Check to see if the ball hit the floor
void Tp2Simulation::checkFloor()
{
    // Do nothing if the something has already been crossed
    if ( mIsFloorCrossed || mIsGoalCrossed || mIsSoccerFieldCrossed )
        return;

    // The ball is below zero, since we check if it outside before this, 
    // the ball must be inside the field at the moment
    if ( mBallPosition.z() < 0.0f )
    {
        // The very last is == mBallPosition so the one before mBallPosition is size() - 2
        Vector4d lastBallPosition = mBallPositions[mBallPositions.size() - 2];
        Vector4d estimatedPosition = MathUtils<DOUBLE>::interpolate4(lastBallPosition, mBallPosition, 
                                                                     0.0f, COMPONENT_Z);

		printHeader("La balle a atterie sur le terrain (Echec)");
        printResult(estimatedPosition);

        mIsFloorCrossed = TRUE;
    }
}

void Tp2Simulation::printHeader(const CHAR* title)
{
    cout << "=========================== Resultats ============================= " << endl << endl;
    cout << "  " << title << endl;
}

void Tp2Simulation::printResult(const Vector4d& estimatedPosition)
{
    // Replace last ball position with the estimated position at the end
    mBallPositions[mBallPositions.size() - 1] = estimatedPosition;

    cout << endl;
	cout << "Position Initiale   : " << Tp2Constants::INITIAL_POSITION << " metres" << endl;
	cout << "Vitesse  Initiale   : " << mInitialLinearVelocity << " (" 
									 << mInitialLinearVelocity.magnitude() << ") metres/seconde" << endl;
	cout << "Vitesse  Angulaire  : " << mInitialAngularVelocity << " radians/seconde" << endl;
	cout << "------------------------------------------------------------------- " << endl;
    cout << "Position Finale     : " << estimatedPosition << " metres" << endl;
    cout << "Vitesse  Finale     : " << sLinearVelocity << " (" 
		                             << sLinearVelocity.magnitude() << ") metres/seconde" << endl;
	cout << "------------------------------------------------------------------- " << endl;
	// -1 Because we don't count the initial value
    cout << "Nombre d'iterations : " << mBallPositions.size() - 1 << endl; 
    cout << "Temps Ecoule        : " << setprecision(3) << estimatedPosition.w() << " secondes" << endl << endl;
    cout << "============================== Fin ================================ " << endl << endl;
}