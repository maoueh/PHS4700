#ifndef COMMON_H
#define COMMON_H

#define EMPTY_SHADER_PROGRAM 0
#define WINDOWED_MODE        TRUE

#define HALF_PI   1.570795f
#define PI        3.141590f
#define DOUBLE_PI 6.283180f
#define DEG2RAD( a ) ( a / 180.0f ) * ( PI )
#define RAD2DEG( a ) ( a * 180.0f ) / ( PI )
#define CLIP( a, min, max ) ( a < min ) ? min : ( ( a > max ) ? max : a )
#define EPSILON 0.00001f
#define MAX( a, max ) ( a < max ) ? ( max ) : ( a )
#define MIN( a, min ) ( a > min ) ? ( min ) : ( a )

#define COMPONENT_X 0
#define COMPONENT_Y 1
#define COMPONENT_Z 2
#define COMPONENT_W 3

#define COMPONENT_R 0
#define COMPONENT_G 1
#define COMPONENT_B 2

// Precompiled headers
#include "precompiled_headers.h"

// Required by every one
#include "types.h"
#include "utils.h"

#endif