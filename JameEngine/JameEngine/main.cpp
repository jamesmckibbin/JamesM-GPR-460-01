#include <stdio.h>
#include <vector>

#include "gameobject.h"

//using namespace std;

int main(int argc, char* argv[])
{
    bool loop = true;

    const int WIDTH = 640;
    const int HEIGHT = 480;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Jame Engine v0.0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    std::vector<Component*> activeComponents {};

    GameObject* player = new GameObject(Vector3{ WIDTH / 2, HEIGHT / 2, 0.f });
    activeComponents.push_back(player->CreateRenderer(20.f, 20.f, Vector3{ 255.f, 0.f, 0.f }));
    activeComponents.push_back(player->CreatePlayerController(0.1f));

    GameObject* rectangle1 = new GameObject(Vector3{ 100, 100, 0.f });
    activeComponents.push_back(rectangle1->CreateRenderer(100.f, 20.f, Vector3{ 255.f, 0.f, 255.f }));

    GameObject* rectangle2 = new GameObject(Vector3{ 500, 500, 0.f });
    activeComponents.push_back(rectangle2->CreateRenderer(50.f, 50.f, Vector3{ 0.f, 255.f, 0.f }));

    Uint32 lastFrameStartTime, deltaTime = 0;

    while (loop) {
        lastFrameStartTime = SDL_GetTicks();

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            
        }
        // UPDATE
        for (Component* comp : activeComponents) {
            comp->Update((float)deltaTime);
        }
        // DRAW
        SDL_RenderClear(renderer);
        player->GetRenderer()->Draw(renderer, player->transform.position);
        rectangle1->GetRenderer()->Draw(renderer, rectangle1->transform.position);
        rectangle2->GetRenderer()->Draw(renderer, rectangle2->transform.position);
        SDL_RenderPresent(renderer);

        deltaTime = SDL_GetTicks() - lastFrameStartTime;
    }

    delete player;
    player = nullptr;
    delete rectangle1;
    delete rectangle2;
    rectangle1 = nullptr;
    rectangle2 = nullptr;

    SDL_DestroyRenderer(renderer); 
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}