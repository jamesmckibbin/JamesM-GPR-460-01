#pragma once

#include "stackallocator.h"
#include "level.h"

class Stage {
public:
    Stage();
    ~Stage();

    void Init();
    void Destroy();
    bool Loop(SDL_Renderer* renderer);
    void DoDebugInput();

    void LoadNewLevel();
    void LoadLevelFromFile(std::string filename);
    void UnloadLevel();

    GameObject* AddRandomGameObject();
    void DeleteClosestGameObject();
    RectangleCollider** ReturnCollisions(RectangleCollider* colToCheck);

    std::vector<GameObject*> activeGameObjects;
private:
    std::vector<Level*> storedLevels;

    GameObject* background = nullptr;
    GameObject* player = nullptr;
    Uint32 lastFrameStartTime, deltaTime = 1;
    bool debugKeyDown = false;
    bool printFPS = false;
    bool chaosMode = false;
};