#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "gameobject.h"
#include "stackallocator.h"
#include <string>

void DoDebugInput();
GameObject* AddRandomGameObject();
void DeleteClosestGameObject();
RectangleCollider** ReturnCollisions(RectangleCollider* colToCheck);

StackAllocator frameAllocator(1028);

GameObject* background;
GameObject* player;

bool debugKeyDown = false;
bool printFPS = false;
bool chaosMode = false;

int main(int argc, char* argv[])
{
    bool loop = true;

    const int WIDTH = 640;
    const int HEIGHT = 480;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Jame Engine v0.0.3", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    srand(time(NULL));

    background = new GameObject(Vector3{ WIDTH / 2, HEIGHT / 2, 0.f });
    background->CreateRenderer(WIDTH, HEIGHT, Vector3{ 255.f, 255.f, 255.f });
    Scene::sGameObjects.push_back(background);

    player = new GameObject(Vector3{ WIDTH / 2, HEIGHT / 2, 0.f });
    player->CreateRenderer(20.f, 20.f, Vector3{ 255.f, 0.f, 0.f });
    player->CreatePlayerController(0.1f);
    player->CreateCollider(20.f, 20.f);
    player->CreateColliderColorChanger(Vector3{ 255.f, 0.f, 0.f }, Vector3{ 0.f, 0.f, 0.f });
    Scene::sGameObjects.push_back(player);

    Uint32 lastFrameStartTime, deltaTime = 1;

    while (loop) {
        // FRAME TIME START
        lastFrameStartTime = SDL_GetTicks();

        // FRAME ALLOCATION START
        char* frameCounter = frameAllocator.Alloc<char>();

        // SDL EVENTS
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            
        }

        // DEBUG INPUT
        DoDebugInput();

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

        // CHAOS MODE
        if (chaosMode) {
            switch (rand() % 2 + 1) {
            case 1:
                AddRandomGameObject();
                break;
            case 2:
                DeleteClosestGameObject();
                break;
            default:
                break;
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

        // FPS COUNTER
        if (printFPS) {
            if (frameCounter != nullptr) {
                snprintf(frameCounter, frameAllocator.BytesFree(), "FPS: %d", 1000 / deltaTime);
                puts(frameCounter);
            }
            else {
                puts("Could not print frame counter, not enough memory");
            }
            printFPS = false;
        }

        // FRAME ALLOCATION RESET
        frameAllocator.Reset();

        // FRAME TIME END
        deltaTime = SDL_GetTicks() - lastFrameStartTime;
    }

    // CLEAN UP GAME OBJECTS
    for (GameObject* obj : Scene::sGameObjects) {
        delete obj;
        obj = nullptr;
    }
    Scene::sGameObjects.clear();

    // EXIT APPLICATION
    SDL_DestroyRenderer(renderer); 
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void DoDebugInput() {
    const Uint8* keyboard = SDL_GetKeyboardState(NULL);
    // NEW GAME OBJECT
    if (keyboard[SDL_SCANCODE_SPACE]) {
        if (!debugKeyDown) {
            AddRandomGameObject();
            debugKeyDown = true;
        }
    }
    // DELETE NEAREST GAME OBJECT
    else if (keyboard[SDL_SCANCODE_D]) {
        if (!debugKeyDown) {
            DeleteClosestGameObject();
            debugKeyDown = true;
        }
    }
    // TOGGLE CHAOS MODE
    else if (keyboard[SDL_SCANCODE_R]) {
        if (!debugKeyDown) {
            chaosMode = !chaosMode;
            debugKeyDown = true;
        }
    }
    // FILL EACH POOL
    else if (keyboard[SDL_SCANCODE_F]) {
        if (!debugKeyDown) {
            // (should fill the pool here :) )
            debugKeyDown = true;
        }
    }
    // EMPTY EACH POOL (EXCEPT FOR PLAYER)
    else if (keyboard[SDL_SCANCODE_C]) {
        if (!debugKeyDown) {
            for (GameObject* obj : Scene::sGameObjects) {
                DeleteClosestGameObject();
            }
            debugKeyDown = true;
        }
    }
    // PRINT FPS
    else if (keyboard[SDL_SCANCODE_T]) {
        if (!debugKeyDown) {
            printFPS = true;
        }
        debugKeyDown = true;
    }
    // PRINT NUM COLLISIONS WITH PLAYER
    else if (keyboard[SDL_SCANCODE_Q]) {
        if (!debugKeyDown) {
            ReturnCollisions(player->GetCollider());
        }
        debugKeyDown = true;
    }
    // RESET ON NO BUTTONS PRESSED
    else if (debugKeyDown) {
        debugKeyDown = false;
    }
}

GameObject* AddRandomGameObject() {
    // Set up random values
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
        Scene::sGameObjects.push_back(newGO);
        return newGO;
    }
    else {
        delete newGO;
        newGO = nullptr;
        return nullptr;
    }
}

void DeleteClosestGameObject() {
    GameObject* closestGO = nullptr;
    for (GameObject* obj : Scene::sGameObjects) {
        if (obj != player && obj != background) {
            // Get closest
            if (closestGO == nullptr) {
                closestGO = obj;
            }
            else if (abs(obj->transform.position.x - player->transform.position.x) + abs(obj->transform.position.y - player->transform.position.y) <
                     abs(closestGO->transform.position.x - player->transform.position.x) + abs(closestGO->transform.position.y - player->transform.position.y)) {
                closestGO = obj;
            }
        }
    }
    if (closestGO != nullptr) {
        Scene::sGameObjects.erase(std::remove(Scene::sGameObjects.begin(), Scene::sGameObjects.end(), closestGO));
        delete closestGO;
        closestGO = nullptr;
    }
}

RectangleCollider** ReturnCollisions(RectangleCollider* colToCheck) {
    RectangleCollider** colliders = frameAllocator.AllocArray<RectangleCollider*>(Scene::sRectangleColliderPool.GetSize());
    int nextIndex = 0;
    if (colliders != nullptr) {
        for (int i = 0; i < Scene::sRectangleColliderPool.GetSize(); i++) {
            if (colToCheck->CheckCollision(Scene::sRectangleColliderPool.GetPoolArrayItem(i)) && 
                colToCheck != Scene::sRectangleColliderPool.GetPoolArrayItem(i)) {
                colliders[nextIndex] = Scene::sRectangleColliderPool.GetPoolArrayItem(i);
                nextIndex++;
            }
        }
    }
    std::string printString = "Num of collisions with checked collider: " + std::to_string(nextIndex);
    std::cout << printString << std::endl;
    return colliders;
}