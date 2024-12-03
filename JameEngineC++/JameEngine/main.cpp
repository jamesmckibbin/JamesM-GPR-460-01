#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "stage.h"

int main(int argc, char* argv[])
{
    bool loop = true;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Jame Engine v0.0.3", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    srand(time(NULL));

    Stage* stage = new Stage();

    while (loop) {
        loop = stage->Loop(renderer);
    }

    stage->Destroy();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}