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

    std::vector<GameObject*> activeGOs {};
    std::vector<Component*> activeComponents {};

    // for convienence
    std::vector<RectangleCollider*> activeColliders {};

    GameObject* background = new GameObject(Vector3{ WIDTH / 2, HEIGHT / 2, 0.f });
    activeGOs.push_back(background);
    activeComponents.push_back(background->CreateRenderer(WIDTH, HEIGHT, Vector3{ 255.f, 255.f, 255.f }));

    GameObject* rectangle1 = new GameObject(Vector3{ 100.f, 100.f, 0.f });
    activeGOs.push_back(rectangle1);
    activeComponents.push_back(rectangle1->CreateRenderer(100.f, 20.f, Vector3{ 100.f, 0.f, 100.f }));
    activeComponents.push_back(rectangle1->CreateCollider(100.f, 20.f));
    activeColliders.push_back(rectangle1->GetCollider());

    GameObject* player = new GameObject(Vector3{ WIDTH / 2, HEIGHT / 2, 0.f });
    activeGOs.push_back(player);
    activeComponents.push_back(player->CreateRenderer(20.f, 20.f, Vector3{ 255.f, 0.f, 0.f }));
    activeComponents.push_back(player->CreatePlayerController(0.1f));
    activeComponents.push_back(player->CreateCollider(20.f, 20.f));
    activeColliders.push_back(player->GetCollider());
    activeComponents.push_back(player->CreateColliderColorChanger(Vector3{ 255.f, 0.f, 0.f }, Vector3{ 0.f, 0.f, 0.f }));

    Uint32 lastFrameStartTime, deltaTime = 0;

    while (loop) {
        lastFrameStartTime = SDL_GetTicks();

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            
        }
        // UPDATE
        for (int i = 0; i < activeColliders.size(); i++) {
            for (int j = i + 1; j < activeColliders.size(); j++) {
                if (activeColliders[i]->CheckCollision(activeColliders[j])) {
                    activeColliders[i]->isColliding = true;
                    activeColliders[j]->isColliding = true;
                }
                else {
                    activeColliders[i]->isColliding = false;
                    activeColliders[j]->isColliding = false;
                }
            }
        }
        for (Component* comp : activeComponents) {
            comp->Update((float)deltaTime);
        }
        // DRAW
        SDL_RenderClear(renderer);
        for (GameObject* go : activeGOs) {
            go->GetRenderer()->Draw(renderer, go->transform.position);
        }
        SDL_RenderPresent(renderer);

        deltaTime = SDL_GetTicks() - lastFrameStartTime;
    }

    delete background;
    background = nullptr;
    delete player;
    player = nullptr;
    delete rectangle1;
    rectangle1 = nullptr;

    SDL_DestroyRenderer(renderer); 
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}