#include "tp1_constants.h"

Vector Tp1Constants::INITIAL_POSITION = Vector(4.0f, 7.5f, 0.5f);
Vector Tp1Constants::INITIAL_VELOCITY = Vector(-2.0f, 10.0f, 7.5f);
Vector Tp1Constants::GRAVITY = Vector(0.0f, 0.0f, -9.80f);

FLOAT Tp1Constants::SIMULATION_1_TIME_STEP = 0.005f;
FLOAT Tp1Constants::SIMULATION_2_TIME_STEP = 0.005f;

FLOAT Tp1Constants::COURT_WIDTH = 8.23f;
FLOAT Tp1Constants::COURT_LENGTH = 23.78f;
FLOAT Tp1Constants::COURT_REACH = 2.5f; // The reach is the highest point where the ball can be hit

FLOAT Tp1Constants::PLAYER_ZONE_WIDTH = COURT_WIDTH;
FLOAT Tp1Constants::PLAYER_ZONE_LENGTH = COURT_LENGTH / 2.0f;

FLOAT Tp1Constants::NET_HEIGHT = 0.914f;

FLOAT Tp1Constants::BALL_RADIUS = 0.0635f;
FLOAT Tp1Constants::BALL_MASS = 0.0567f;

FLOAT Tp1Constants::SPEED_REDUCTION_CONSTANT = 0.01f; // Constant k in the assigment

FLOAT Tp1Constants::CAMERA_THETA_ROTATION_SPEED = 4.5f;
FLOAT Tp1Constants::CAMERA_PHI_ROTATION_SPEED = 2.5f;