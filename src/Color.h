#ifndef COLOR_H_
#define COLOR_H_

#include "BasicTypes.h"

typedef struct {
    union {
        f32 values[4];
        struct {
            f32 r;
            f32 g;
            f32 b;
            f32 a;
        };
    };
} Color;

Color Color_FromU32(u32 rgba);
u32 Color_ToU32(Color color);

#endif