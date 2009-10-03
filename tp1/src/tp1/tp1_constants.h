#ifndef TP1_CONSTANTS_H
#define TP1_CONSTANTS_H

#include "common.h"

#define SIMULATION_TYPE_1 1
#define SIMULATION_TYPE_2 2

class Tp1Constants
{
public:

    // In Meter/Second^2
    static Vector GRAVITY;
    
    // In Meter
    static Vector INITIAL_POSITION;

    // In Meter/Second
    static Vector INITIAL_VELOCITY;

    // In second
    static FLOAT  SIMULATION_1_TIME_STEP;
    static FLOAT  SIMULATION_2_TIME_STEP;

    // In Meter
    static FLOAT COURT_WIDTH;
    static FLOAT COURT_LENGTH;
    static FLOAT COURT_REACH; // The reach is the highest point where the ball can be hit

    // In Meter
    static FLOAT PLAYER_ZONE_WIDTH;
    static FLOAT PLAYER_ZONE_LENGTH;

    static FLOAT NET_HEIGHT;

    static FLOAT BALL_RADIUS;

    // In Kilogram
    static FLOAT BALL_MASS;

    // In Second
    static FLOAT SPEED_REDUCTION_CONSTANT; // Constant k in the assigment

    // Unit 
    static FLOAT CAMERA_THETA_ROTATION_SPEED;
    static FLOAT CAMERA_PHI_ROTATION_SPEED;

private:
    // Class cannot be instantiated
    Tp1Constants();
    Tp1Constants(const Tp1Constants& other);
    Tp1Constants& operator=(const Tp1Constants& rightSide);

};

#endif