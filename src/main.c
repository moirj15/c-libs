#include "Array.h"
#include "GenericAllocator.h"
#include "Rasterizer.h"

#include <stdio.h>
#include <SDL2/SDL.h>

int main(int argc, char **argv)
{
    Rasterizer *rasterizer = Rasterizer_init(1920, 1080);

    while (true) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                Rasterizer_destroy(rasterizer);
                return 0;
            }
        }
        Rasterizer_clear_screen(rasterizer, (Color){1.0f, 0.0f, 0.0f, 1.0f});
        Rasterizer_swap_buffers(rasterizer);
        Rasterizer_present(rasterizer);
    }

//    return 0;
}
