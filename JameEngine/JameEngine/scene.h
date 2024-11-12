#pragma once

#include "stackallocator.h"
#include "level.h"

class Scene {
public:
    Scene();
    ~Scene();

    void Init();
    void Destroy();
    bool Loop(SDL_Renderer* renderer);
    void DoDebugInput();

    bool LoadLevel(std::string filename);

    GameObject* AddRandomGameObject();
    void DeleteClosestGameObject();
    RectangleCollider** ReturnCollisions(RectangleCollider* colToCheck);

    std::vector<GameObject*> activeGameObjects;
private:
    GameObject* background = nullptr;
    GameObject* player = nullptr;
    Uint32 lastFrameStartTime, deltaTime = 1;
    bool debugKeyDown = false;
    bool printFPS = false;
    bool chaosMode = false;
};