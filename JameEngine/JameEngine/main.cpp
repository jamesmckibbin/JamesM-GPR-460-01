#include <stdio.h>
#include <iostream>

#include <unordered_map>

#include "gameobject.h"

using namespace std;

float deltatime = 1000/60;
bool loop = true;

int main(int argc, char* argv[])
{
    const int WIDTH = 640;
    const int HEIGHT = 480;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Jame Engine v0.0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    GameObject* player = new GameObject(Vector3{ WIDTH / 2, HEIGHT / 2, 0.f });
    player->CreateRenderer(20.f, 20.f, Vector3{ 255.f, 0.f, 0.f });

    while (loop) {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // INPUT
            const Uint8* keyboard = SDL_GetKeyboardState(NULL);

            // EXIT
            if (keyboard[SDL_SCANCODE_ESCAPE]) {
                loop = false;
            }

            // VERTICAL
            if (keyboard[SDL_SCANCODE_W]) {
                player->transform.position.y -= deltatime;
            }
            else if (keyboard[SDL_SCANCODE_S]) {
                player->transform.position.y += deltatime;
            }

            // HORIZONTAL
            if (keyboard[SDL_SCANCODE_A]) {
                player->transform.position.x -= deltatime;
            }
            else if (keyboard[SDL_SCANCODE_D]) {
                player->transform.position.x += deltatime;
            }
            // UPDATE

            // DRAW
            SDL_RenderClear(renderer);
            player->GetRenderer()->Draw(renderer, player->transform.position);
            SDL_RenderPresent(renderer);
        }
    }

    delete player;
    player = nullptr;

    SDL_DestroyRenderer(renderer); 
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}