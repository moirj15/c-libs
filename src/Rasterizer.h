#ifndef RASTERIZER_H_
#define RASTERIZER_H_

#include "Array.h"
#include "BasicTypes.h"
#include "Color.h"
#include "GenericAllocator.h"

#include <SDL2/SDL.h>

typedef struct Rasterizer {
    SDL_Window *sdl_window;
    SDL_Texture *sdl_texture;
    SDL_Renderer *sdl_renderer;
    u32 width;
    u32 height;

    DynamicArray(u32) present_buffer;
    DynamicArray(u32) back_buffer;
    DynamicArray(f32) depth_buffer;
} Rasterizer;

/// Assuming the backbuffer will be the same dimensions as the window
Rasterizer *Rasterizer_init(u32 window_width, u32 window_height);

void Rasterizer_draw_quad(Rasterizer *rasterizer, f32 pixel_coords[2 * 4], Color fill_color);

void Rasterizer_draw_triangles(Rasterizer *rasterizer, f32 *verices, Color *vertex_colors, u64 vertex_count);

void Rasterizer_clear_screen(Rasterizer *rasterizer, Color color);

void Rasterizer_swap_buffers(Rasterizer *rasterizer);

void Rasterizer_present(Rasterizer *rasterizer);

void Rasterizer_destroy(Rasterizer *rasterizer);

#endif // RASTERIZER_H_

