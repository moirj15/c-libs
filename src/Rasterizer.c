#include "Rasterizer.h"

#include <stdio.h>
#include <stdlib.h>

Rasterizer *Rasterizer_init(u32 window_width, u32 window_height)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Failed to initialize SDL2 for video: %s\n", SDL_GetError());
    }

    SDL_Window *sdl_window = NULL;
    sdl_window = SDL_CreateWindow(
        "window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_SHOWN);

    if (!sdl_window) {
        fprintf(stderr, "Failed to create SDL window: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Renderer *sdl_renderer = SDL_CreateRenderer(sdl_window, -1, 0);

    if (!sdl_renderer) {
        fprintf(stderr, "Failed to create SDL Renderer: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Texture *sdl_texture = SDL_CreateTexture(
        sdl_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, window_width, window_height);

    if (!sdl_texture) {
        fprintf(stderr, "Failed to create SDL Texture: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    Rasterizer *rasterizer = GenericAllocator_Malloc(sizeof(Rasterizer));
    *rasterizer = (Rasterizer){
        .sdl_window = sdl_window,
        .sdl_texture = sdl_texture,
        .sdl_renderer = sdl_renderer,
        .width = window_width,
        .height = window_height,
        .present_buffer = DynamicArray_init_with_size(u32, window_width * window_height),
        .back_buffer = DynamicArray_init_with_size(u32, window_width * window_height),
        .depth_buffer = DynamicArray_init_with_size(f32, window_width * window_height),
    };

    return rasterizer;
}

void Rasterizer_draw_quad(Rasterizer *rasterizer, f32 pixel_coords[2 * 4], Color fill_color)
{
}

void Rasterizer_draw_triangles(Rasterizer *rasterizer, f32 *verices, Color *vertex_colors, u64 vertex_count)
{
}

void Rasterizer_clear_screen(Rasterizer *rasterizer, Color color)
{
    u32 color_word = Color_ToU32(color);
    for (u32 i = 0; i < DynamicArray_size(rasterizer->back_buffer); i++) {
        rasterizer->back_buffer[i] = color_word;
    }
}

void Rasterizer_swap_buffers(Rasterizer *rasterizer)
{
    u32 *tmp = rasterizer->present_buffer;
    rasterizer->present_buffer = rasterizer->back_buffer;
    rasterizer->back_buffer = tmp;
}

void Rasterizer_present(Rasterizer *rasterizer)
{
    SDL_UpdateTexture(rasterizer->sdl_texture, NULL, rasterizer->present_buffer, rasterizer->width * sizeof(uint32_t));

    SDL_RenderClear(rasterizer->sdl_renderer);
    SDL_RenderCopy(rasterizer->sdl_renderer, rasterizer->sdl_texture, NULL, NULL);
    SDL_RenderPresent(rasterizer->sdl_renderer);
}

void Rasterizer_destroy(Rasterizer *rasterizer)
{
    DynamicArray_destroy(rasterizer->present_buffer);
    DynamicArray_destroy(rasterizer->back_buffer);
    DynamicArray_destroy(rasterizer->depth_buffer);
    GenericAllocator_Free(rasterizer);
}