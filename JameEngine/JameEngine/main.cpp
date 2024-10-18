#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "gameobject.h"

int main(int argc, char* argv[])
{
    bool loop = true;
    bool chaosMode = false;
    bool debugKeyDown = false;

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
        // NEW GAME OBJECT
        if (keyboard[SDL_SCANCODE_SPACE]) {
            if (!debugKeyDown) {
                // Set up random values
                srand(time(NULL));
                Vector3 randomLocation = { player->transform.position.x + rand() % 100 - 50, player->transform.position.y + rand() % 100 - 50, 0.f };
                Vector3 randomColor = { rand() % 255, rand() % 255, rand() % 255 };
                Vector3 randomAltColor = { rand() % 255, rand() % 255, rand() % 255 };
                int randomComponent = rand() & 3 + 1;

                // Instantiate GO
                GameObject* newGO = new GameObject(randomLocation);

                // If possible, create renderer and collider component
                if (Scene::sRectangleRendererPool.CanCreateComponent() && 
                    Scene::sRectangleColliderPool.CanCreateComponent()) {
                    newGO->CreateRenderer(10.f, 10.f, randomColor);
                    newGO->CreateCollider(10.f, 10.f);
                    gameObjects.push_back(newGO);
                    printf("Object created");
                }
                else {
                    delete newGO;
                    newGO = nullptr;
                }
                
                debugKeyDown = true;
            }
        }
        // DELETE NEAREST GAME OBJECT
        else if (keyboard[SDL_SCANCODE_D]) {
            if (!debugKeyDown) {
                GameObject* closestGO = nullptr;
                for (GameObject* obj : gameObjects) {
                    if (obj != player && obj != background) {
                        closestGO = obj;
                    }
                }
                if (closestGO != nullptr) {
                    gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), closestGO));
                    delete closestGO;
                    closestGO = nullptr;
                }

                printf("D pressed");
                debugKeyDown = true;
            }
        }
        // TOGGLE CHAOS MODE
        else if (keyboard[SDL_SCANCODE_R]) {
            if (!debugKeyDown) {
                printf("R pressed");
                chaosMode = !chaosMode;
                debugKeyDown = true;
            }
        }
        // FILL EACH POOL
        else if (keyboard[SDL_SCANCODE_F]) {
            if (!debugKeyDown) {
                printf("F pressed");
                debugKeyDown = true;
            }
        }
        // EMPTY EACH POOL (EXCEPT FOR PLAYER)
        else if (keyboard[SDL_SCANCODE_C]) {
            if (!debugKeyDown) {
                for (GameObject* obj : gameObjects) {
                    if (obj != player && obj != background) {
                        gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), obj));
                        delete obj;
                        obj = nullptr;
                    }
                }
                printf("C pressed");
                debugKeyDown = true;
            }
        }
        else if (debugKeyDown) {
            debugKeyDown = false;
        }
        

        // COLLISIONS
        for (int i = 0; i < Scene::sRectangleColliderPool.GetSize(); i++) {
            for (int j = i + 1; j < Scene::sRectangleColliderPool.GetSize(); j++) {
                if (Scene::sRectangleColliderPool.GetPoolArrayItemInUse(i) &&
                    Scene::sRectangleColliderPool.GetPoolArrayItemInUse(j)) {
                    if (Scene::sRectangleColliderPool.GetPoolArrayItem(i)->CheckCollision(Scene::sRectangleColliderPool.GetPoolArrayItem(j))) {
                        Scene::sRectangleColliderPool.GetPoolArrayItem(i)->isColliding = true;
                        Scene::sRectangleColliderPool.GetPoolArrayItem(j)->isColliding = true;
                    }
                    else {
                        Scene::sRectangleColliderPool.GetPoolArrayItem(i)->isColliding = false;
                        Scene::sRectangleColliderPool.GetPoolArrayItem(j)->isColliding = false;
                    }
                }
            }
        }

        // UPDATE
        for (int i = 0; i < Scene::sPlayerControllerPool.GetSize(); i++) {
            if (Scene::sPlayerControllerPool.GetPoolArrayItemInUse(i)) {
                Scene::sPlayerControllerPool.GetPoolArrayItem(i)->Update(deltaTime);
            }
        }
        for (int i = 0; i < Scene::sRectangleColliderPool.GetSize(); i++) {
            if (Scene::sRectangleColliderPool.GetPoolArrayItemInUse(i)) {
                Scene::sRectangleColliderPool.GetPoolArrayItem(i)->Update(deltaTime);
            }
        }
        for (int i = 0; i < Scene::sColliderColorChangerPool.GetSize(); i++) {
            if (Scene::sColliderColorChangerPool.GetPoolArrayItemInUse(i)) {
                Scene::sColliderColorChangerPool.GetPoolArrayItem(i)->Update(deltaTime);
            }
        }

        // DRAW
        SDL_RenderClear(renderer);
        for (int i = 0; i < Scene::sRectangleRendererPool.GetSize(); i++) {
            if (Scene::sRectangleRendererPool.GetPoolArrayItemInUse(i)) {
                Scene::sRectangleRendererPool.GetPoolArrayItem(i)->Draw(renderer, Scene::sRectangleRendererPool.GetPoolArrayItem(i)->GetOwningGameObject()->transform.position);
            }
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