#ifndef TP2_CONSTANTS_H
#define TP2_CONSTANTS_H

#include "game_engine_lib.h"

class Tp2Constants
{
public:

    // In Meters/Second^2
    static Vector3d GRAVITY;
    
    // In Meter
    static Vector4d INITIAL_POSITION;

    // In Meters/Second
    static Vector4d INITIAL_LINEAR_VELOCITY;
    // In Radians/Second
    static Vector4d INITIAL_ANGULAR_VELOCITY;

    // In seconds
    static DOUBLE  SIMULATION_TIME_STEP;

    // In Degree Celsius
    static DOUBLE SOCCER_FIELD_TEMP;
    // In kg/m^3
    static DOUBLE AIR_DENSITY;
    // Scalar
    static DOUBLE AIR_VISCOSITY;

    // In Meter
    static DOUBLE SOCCER_FIELD_LENGTH;
    static DOUBLE SOCCER_FIELD_HALF_LENGTH;
    static DOUBLE SOCCER_FIELD_WIDTH;

    // In Meter
    static DOUBLE PENALTY_BOX_LENGTH;
    static DOUBLE PENALTY_BOX_WIDTH;
    static DOUBLE PENALTY_BOX_OFFSET_X;

    // In Meter
    static DOUBLE GOAL_BOX_LENGTH;
    static DOUBLE GOAL_BOX_WIDTH;
    static DOUBLE GOAL_BOX_OFFSET_X;

    // In Meter
    static DOUBLE GOAL_LENGTH;
    static DOUBLE GOAL_WIDTH;
    static DOUBLE GOAL_OFFSET_X;
    static DOUBLE GOAL_OFFSET_Y;

    static DOUBLE GOAL_START_X;
    static DOUBLE GOAL_END_X;
    static DOUBLE GOAL_START_Z;
    static DOUBLE GOAL_END_Z;

    // In Meter
    static DOUBLE SOCCER_BALL_RADIUS;
    // In Kilogram
    static DOUBLE SOCCER_BALL_MASS;

    // Unit 
    static DOUBLE CAMERA_THETA_ROTATION_SPEED;
    static DOUBLE CAMERA_PHI_ROTATION_SPEED;
    static DOUBLE CAMERA_RHO_WHEEL_REDUCTION_SPEED;

    static BOOL SKIP_DATA_INPUT;

    static Vector4d QUARTER_1;
    static Vector4d QUARTER_2;
    static Vector4d QUARTER_3;
    static Vector4d QUARTER_4;
    static Vector4d QUARTER_5;
    static Vector4d QUARTER_6;
    static Vector4d QUARTER_7;
    static Vector4d QUARTER_8;

    static const INT QUARTER_COUNT = 8;
private:
    // Class cannot be instantiated
    Tp2Constants();
    Tp2Constants(const Tp2Constants& other);
    Tp2Constants& operator=(const Tp2Constants& rightSide);

};

#endif