#include <stdio.h>
#include <vector>

#include "gameobject.h"
#include "componentpool.h"

//using namespace std;

struct Scene {
    
    static ComponentPool<PlayerController> playerControllerPool;
    static ComponentPool<RectangleRenderer> rectangleRendererPool;
    static ComponentPool<RectangleCollider> rectangleColliderPool;
    static ComponentPool<ColliderColorChanger> colliderColorChangerPool;
};

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

    Scene::playerControllerPool = ComponentPool<PlayerController>(15);
    Scene::rectangleRendererPool = ComponentPool<RectangleRenderer>(15);
    Scene::rectangleColliderPool = ComponentPool<RectangleCollider>(15);
    Scene::colliderColorChangerPool = ComponentPool<ColliderColorChanger>(15);

    GameObject* background = new GameObject(Vector3{ WIDTH / 2, HEIGHT / 2, 0.f });
    Scene::rectangleRendererPool.New(RectangleRenderer(background, WIDTH, HEIGHT, Vector3{ 255.f, 255.f, 255.f }));
    gameObjects.push_back(background);

    GameObject* rectangle1 = new GameObject(Vector3{ 100.f, 100.f, 0.f });
    Scene::rectangleRendererPool.New(RectangleRenderer(rectangle1, 100.f, 20.f, Vector3{ 100.f, 0.f, 100.f }));
    Scene::rectangleColliderPool.New(RectangleCollider(rectangle1, 100.f, 20.f));
    gameObjects.push_back(rectangle1);

    GameObject* player = new GameObject(Vector3{ WIDTH / 2, HEIGHT / 2, 0.f });
    Scene::rectangleRendererPool.New(RectangleRenderer(player, 20.f, 20.f, Vector3{ 255.f, 0.f, 0.f }));
    Scene::playerControllerPool.New(PlayerController(player, 0.1f));
    Scene::rectangleColliderPool.New(RectangleCollider(player, 20.f, 20.f));
    Scene::colliderColorChangerPool.New(ColliderColorChanger(player, Vector3{ 255.f, 0.f, 0.f }, Vector3{ 0.f, 0.f, 0.f }));
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

        // UPDATE
        for (int i = 0; i < Scene::rectangleColliderPool.GetPoolSize(); i++) {
            for (int j = i + 1; j < Scene::rectangleColliderPool.GetPoolSize(); j++) {
                if (Scene::rectangleColliderPool[i]->CheckCollision(activeColliders[j])) {
                    activeColliders[i]->isColliding = true;
                    activeColliders[j]->isColliding = true;
                }
                else {
                    activeColliders[i]->isColliding = false;
                    activeColliders[j]->isColliding = false;
                }
            }
        }
        // DRAW
        SDL_RenderClear(renderer);
        for (RectangleRenderer rect : Scene::rectangleRendererPool.GetPoolSize()) {
            rect.Draw(renderer, rect.GetOwningGameObject()->transform.position);
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