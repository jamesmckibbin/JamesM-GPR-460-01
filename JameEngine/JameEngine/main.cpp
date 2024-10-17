#include <stdio.h>
#include <vector>

#include "gameobject.h"
#include "componentpool.h"

int main(int argc, char* argv[])
{
    bool loop = true;

    const int WIDTH = 640;
    const int HEIGHT = 480;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Jame Engine v0.0.2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    std::vector<GameObject*> gameObjects;

    GameObject* background = new GameObject(Vector3{ WIDTH / 2, HEIGHT / 2, 0.f });
    background->CreateRenderer(WIDTH, HEIGHT, Vector3{ 255.f, 255.f, 255.f });
    gameObjects.push_back(background);

    GameObject* rectangle1 = new GameObject(Vector3{ 100.f, 100.f, 0.f });
    rectangle1->CreateRenderer(100.f, 20.f, Vector3{ 100.f, 0.f, 100.f });
    rectangle1->CreateCollider(100.f, 20.f);
    gameObjects.push_back(rectangle1);

    GameObject* player = new GameObject(Vector3{ WIDTH / 2, HEIGHT / 2, 0.f });
    player->CreateRenderer(20.f, 20.f, Vector3{ 255.f, 0.f, 0.f });
    player->CreatePlayerController(0.1f);
    player->CreateCollider(20.f, 20.f);
    player->CreateColliderColorChanger(Vector3{ 255.f, 0.f, 0.f }, Vector3{ 0.f, 0.f, 0.f });
    gameObjects.push_back(player);

    Uint32 lastFrameStartTime, deltaTime = 0;

    while (loop) {
        lastFrameStartTime = SDL_GetTicks();

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            
        }
        // DEBUG INPUTS
        
        const Uint8* keyboard = SDL_GetKeyboardState(NULL);
        if (keyboard[SDL_SCANCODE_SPACE]) {
            // Spawn GO close to player
        } 
        else if (keyboard[SDL_SCANCODE_D]) {
            // Delete closest GO to player
        }
        else if (keyboard[SDL_SCANCODE_R]) {
            // Toggle random creation and deletion state
        }
        else if (keyboard[SDL_SCANCODE_F]) {
            // Fill pool
        }
        else if (keyboard[SDL_SCANCODE_C]) {
            // Clear pool except for player
        }

        //// UPDATE
        //for (int i = 0; i < gRectangleColliderPool.GetPool().size(); i++) {
        //    for (int j = i + 1; j < gRectangleColliderPool.GetPool().size(); j++) {
        //        if (gRectangleColliderPool.GetPool()[i]->CheckCollision(gRectangleColliderPool.GetPool()[j])) {
        //            gRectangleColliderPool.GetPool()[i]->isColliding = true;
        //            gRectangleColliderPool.GetPool()[j]->isColliding = true;
        //        }
        //        else {
        //            gRectangleColliderPool.GetPool()[i]->isColliding = false;
        //            gRectangleColliderPool.GetPool()[j]->isColliding = false;
        //        }
        //    }
        //}
        // DRAW
        SDL_RenderClear(renderer);
        for (GameObject* obj : gameObjects) {
            obj->Draw(renderer);
        }
        SDL_RenderPresent(renderer);

        deltaTime = SDL_GetTicks() - lastFrameStartTime;
    }

    for (GameObject* obj : gameObjects) {
        delete obj;
        obj = nullptr;
    }
    gameObjects.clear();

    SDL_DestroyRenderer(renderer); 
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}