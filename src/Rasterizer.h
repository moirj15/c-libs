#ifndef RASTERIZER_H_
#define RASTERIZER_H_

#include "BasicTypes.h"

typedef struct Rasterizer Rasterizer;

/// Assuming the backbuffer will be the same dimensions as the window
Rasterizer *Rasterizer_Init(u32 window_width, u32 window_height);

void Rasterizer_Destroy(Rasterizer *rasterizer);

#endif // RASTERIZER_H_
