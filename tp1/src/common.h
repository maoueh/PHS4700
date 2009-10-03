#ifndef COMMON_H
#define COMMON_H

#define EMPTY_SHADER_PROGRAM 0
#define WINDOWED_MODE        TRUE

#define HALF_PI   1.570795f
#define PI        3.141590f
#define DOUBLE_PI 6.283180f
#define DEG2RAD( a ) ( a / 180.0f ) * ( PI )
#define CLIP( a, min, max ) ( a < min ) ? min : ( ( a > max ) ? max : a )
#define EPSILON 0.00001f
#define MAX( a, max ) ( a < max ) ? ( max ) : ( a )
#define MIN( a, min ) ( a > min ) ? ( min ) : ( a )

#include "precompiled_headers.h"

#include "types.h"
#include "utils.h"
#include "vector4.h"

#endif