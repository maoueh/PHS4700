#include "tp2_constants.h"

BOOL Tp2Constants::SKIP_DATA_INPUT = TRUE;

Vector4d Tp2Constants::INITIAL_POSITION         = Vector4d(0.0f, 0.0f, 0.0f, 0.0f);

/// On the field
//Vector4d Tp2Constants::INITIAL_LINEAR_VELOCITY  = Vector4d(75.0f, 75.0f, 15.0f);
//Vector4d Tp2Constants::INITIAL_ANGULAR_VELOCITY = Vector4d(-PI, 0.0f, -DOUBLE_PI);

/// Outside (right) the field
Vector4d Tp2Constants::INITIAL_LINEAR_VELOCITY  = Vector4d(75.0f, 75.0f, 15.0f);
Vector4d Tp2Constants::INITIAL_ANGULAR_VELOCITY = Vector4d(PI, 0.0f, -DOUBLE_PI);

/// Outside (back) the field
//Vector4d Tp2Constants::INITIAL_LINEAR_VELOCITY  = Vector4d(25.0f, 255.0f, 45.0f);
//Vector4d Tp2Constants::INITIAL_ANGULAR_VELOCITY = Vector4d(0.0f, 0.0f, -DOUBLE_PI);

/// Outside (front) the field
//Vector4d Tp2Constants::INITIAL_LINEAR_VELOCITY  = Vector4d(175.0f, 25.0f, 20.0f);
//Vector4d Tp2Constants::INITIAL_ANGULAR_VELOCITY = Vector4d(0.0f, PI, -DOUBLE_PI);

/// Outside (left) the field
//Vector4d Tp2Constants::INITIAL_LINEAR_VELOCITY  = Vector4d(15.0f, 225.0f, 15.0f);
//Vector4d Tp2Constants::INITIAL_ANGULAR_VELOCITY = Vector4d(-PI, PI, DOUBLE_PI);

/// In the goal
//Vector4d Tp2Constants::INITIAL_LINEAR_VELOCITY  = Vector4d(120.0f, 15.0f, 12.5f);
//Vector4d Tp2Constants::INITIAL_ANGULAR_VELOCITY = Vector4d(0.0f, PI, -DOUBLE_PI);

Vector3d Tp2Constants::GRAVITY = Vector3d(0.0f, 0.0f, -9.80f);

DOUBLE Tp2Constants::SOCCER_FIELD_TEMP = 20;
DOUBLE Tp2Constants::AIR_DENSITY = 1.204f;
DOUBLE Tp2Constants::AIR_VISCOSITY = 0.34f;

DOUBLE Tp2Constants::SIMULATION_TIME_STEP = 0.01f; //0.05

DOUBLE Tp2Constants::SOCCER_BALL_RADIUS = 0.11f; //0.11
DOUBLE Tp2Constants::SOCCER_BALL_MASS = 0.45f;

DOUBLE Tp2Constants::SOCCER_FIELD_LENGTH = 120.0f;
DOUBLE Tp2Constants::SOCCER_FIELD_HALF_LENGTH = 60.0f;
DOUBLE Tp2Constants::SOCCER_FIELD_WIDTH = 90.0f;

DOUBLE Tp2Constants::PENALTY_BOX_LENGTH = 16.5f;
DOUBLE Tp2Constants::PENALTY_BOX_WIDTH = 40.3f;
DOUBLE Tp2Constants::PENALTY_BOX_OFFSET_X = 24.85f;

DOUBLE Tp2Constants::GOAL_BOX_LENGTH = 5.5f;
DOUBLE Tp2Constants::GOAL_BOX_WIDTH = 18.3f;
DOUBLE Tp2Constants::GOAL_BOX_OFFSET_X = 35.85f;

DOUBLE Tp2Constants::GOAL_LENGTH = 1.83f;
DOUBLE Tp2Constants::GOAL_WIDTH = 7.32f;
DOUBLE Tp2Constants::GOAL_OFFSET_X = 41.35f;
DOUBLE Tp2Constants::GOAL_OFFSET_Y = -1.83f;

DOUBLE Tp2Constants::GOAL_START_X = 41.35f;
DOUBLE Tp2Constants::GOAL_END_X = 48.67f;
DOUBLE Tp2Constants::GOAL_START_Z = 0.0f;
DOUBLE Tp2Constants::GOAL_END_Z = 2.44f;

DOUBLE Tp2Constants::CAMERA_THETA_ROTATION_SPEED = 4.5f;
DOUBLE Tp2Constants::CAMERA_PHI_ROTATION_SPEED = 2.5f;
DOUBLE Tp2Constants::CAMERA_RHO_WHEEL_REDUCTION_SPEED = 0.1f;

Vector4d Tp2Constants::QUARTER_1 = Vector4d(1, 1, 1);
Vector4d Tp2Constants::QUARTER_2 = Vector4d(-1, 1, 1);
Vector4d Tp2Constants::QUARTER_3 = Vector4d(1, -1, 1);
Vector4d Tp2Constants::QUARTER_4 = Vector4d(-1, -1, 1);
Vector4d Tp2Constants::QUARTER_5 = Vector4d(1, 1, -1);
Vector4d Tp2Constants::QUARTER_6 = Vector4d(-1, 1, -1);
Vector4d Tp2Constants::QUARTER_7 = Vector4d(1, -1, -1);
Vector4d Tp2Constants::QUARTER_8 = Vector4d(-1, -1, -1);
