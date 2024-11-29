#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>

#include "utils.h"

int main(int argc, char* argv[]) {
    bool loop = true;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Jame Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    while(loop) {
        SDL_Event event;
        SDL_PollEvent(&event);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}