#include "stage.h"

#include <vector>
#include <string>

StackAllocator frameAllocator(1028);

Stage::Stage()
{
    activeGameObjects = std::vector<GameObject*>();
    Init();
}

Stage::~Stage()
{
    Destroy();
}

void Stage::Init()
{
    background = new GameObject(Vector3{ SCREENWIDTH / 2, SCREENHEIGHT / 2, 0.f });
    background->CreateRenderer(SCREENWIDTH, SCREENHEIGHT, Vector3{ 255.f, 255.f, 255.f });

    LoadNewLevel();
}

void Stage::Destroy()
{
    for (GameObject* obj : activeGameObjects) {
        delete obj;
        obj = nullptr;
    }
    activeGameObjects.clear();

    delete player;
    player = nullptr;
    delete background;
    background = nullptr;
}

bool Stage::Loop(SDL_Renderer* renderer)
{
    // FRAME TIME START
    lastFrameStartTime = SDL_GetTicks();

    // FRAME ALLOCATION START
    char* frameCounter = frameAllocator.Alloc<char>();

    // SDL EVENTS
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {

    }

    // DEBUG INPUTS
    DoDebugInput();

    // UPDATE
    for (int i = 0; i < GameObject::sPlayerControllerPool.GetSize(); i++) {
        if (GameObject::sPlayerControllerPool.GetPoolArrayItemInUse(i)) {
            GameObject::sPlayerControllerPool.GetPoolArrayItem(i)->Update(deltaTime);
        }
    }
    for (int i = 0; i < GameObject::sRectangleColliderPool.GetSize(); i++) {
        if (GameObject::sRectangleColliderPool.GetPoolArrayItemInUse(i)) {
            GameObject::sRectangleColliderPool.GetPoolArrayItem(i)->Update(deltaTime);
        }
    }
    for (int i = 0; i < GameObject::sColliderColorChangerPool.GetSize(); i++) {
        if (GameObject::sColliderColorChangerPool.GetPoolArrayItemInUse(i)) {
            GameObject::sColliderColorChangerPool.GetPoolArrayItem(i)->Update(deltaTime);
        }
    }

    // CHAOS MODE
    if (chaosMode) {
        switch (rand() % 2 + 1) {
        case 1:
            Stage::AddRandomGameObject();
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
    for (int i = 0; i < GameObject::sRectangleRendererPool.GetSize(); i++) {
        if (GameObject::sRectangleRendererPool.GetPoolArrayItemInUse(i)) {
            GameObject::sRectangleRendererPool.GetPoolArrayItem(i)->Draw(
                renderer, GameObject::sRectangleRendererPool.GetPoolArrayItem(i)->GetOwningGameObject()->transform.position);
        }
    }
    SDL_RenderPresent(renderer);

    // FPS COUNTER
    if (printFPS) {
        if (frameCounter != nullptr) {
            snprintf(frameCounter, frameAllocator.BytesFree(), "FPS: %d", 1000 / deltaTime);
            puts(frameCounter);
        }
        printFPS = false;
    }

    // FRAME ALLOCATION RESET
    frameAllocator.Reset();

    // FRAME TIME END
    deltaTime = SDL_GetTicks() - lastFrameStartTime;
    
    return true;
}

void Stage::DoDebugInput()
{
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
    // LOAD NEW LEVEL
    else if (keyboard[SDL_SCANCODE_F]) {
        if (!debugKeyDown) {
            LoadNewLevel();
            debugKeyDown = true;
        }
    }
    // EMPTY EACH POOL (EXCEPT FOR PLAYER)
    else if (keyboard[SDL_SCANCODE_C]) {
        if (!debugKeyDown) {
            for (GameObject* obj : activeGameObjects) {
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

void Stage::LoadNewLevel()
{
    // Load menu options of pre-exisiting levels
    char levelInput;
    std::cout << "Choose a level ID to load:" << std::endl;
    for (Level* level : storedLevels) {
        std::cout << "[" << level->levelID << "]" << level->levelName << std::endl;
    }
    std::cout << "[" << '&' << "]" << " Load New Level From File" << std::endl;
    std::cin >> levelInput;

    // Resolve input
    if (levelInput == '&') {
        // New level needed from input
        std::string newLevelInput;
        std::cout << "Enter the filename of the new level you would like to load:" << std::endl;
        std::cin >> newLevelInput;
        LoadLevelFromFile(newLevelInput);
    }
    else {
        for (Level* level : storedLevels) {
            if (levelInput == storedLevels[levelInput]->levelID) {
                UnloadLevel();
                for (int i = 0; i < storedLevels[levelInput]->loadedGameObjects.size(); i++) {
                    if (i == 0) {
                        player = storedLevels[levelInput]->loadedGameObjects[i];
                    }
                    else {
                        activeGameObjects.push_back(storedLevels[levelInput]->loadedGameObjects[i]);
                    }
                }
            }
        }
    }
}

void Stage::LoadLevelFromFile(std::string filename)
{
    Level* newLevel = new Level();
    if (newLevel->ReadLevelDataFromFile(LEVELS_PATH + filename)) {
        UnloadLevel();
        for (int i = 0; i < newLevel->loadedGameObjects.size(); i++) {
            if (i == 0) {
                player = newLevel->loadedGameObjects[i];
            } else {
                activeGameObjects.push_back(newLevel->loadedGameObjects[i]);
            }
        }
        storedLevels.push_back(newLevel);
    }
}

void Stage::UnloadLevel() 
{
    for (GameObject* obj : activeGameObjects) {
        delete obj;
        obj = nullptr;
    }
    activeGameObjects.clear();

    delete player;
    player = nullptr;


}

GameObject* Stage::AddRandomGameObject()
{
    // Set up random values
    Vector3 randomLocation = { player->transform.position.x + rand() % 100 - 50, player->transform.position.y + rand() % 100 - 50, 0.f };
    Vector3 randomColor = { rand() % 255, rand() % 255, rand() % 255 };
    Vector3 randomAltColor = { rand() % 255, rand() % 255, rand() % 255 };
    int randomComponent = rand() & 3 + 1;

    // Instantiate GO
    GameObject* newGO = new GameObject(randomLocation);

    // If possible, create renderer and collider component
    if (GameObject::sRectangleRendererPool.CanCreateComponent() &&
        GameObject::sRectangleColliderPool.CanCreateComponent()) {
        newGO->CreateRenderer(10.f, 10.f, randomColor);
        newGO->CreateCollider(10.f, 10.f);
        activeGameObjects.push_back(newGO);
        return newGO;
    }
    else {
        delete newGO;
        newGO = nullptr;
        return nullptr;
    }
}

void Stage::DeleteClosestGameObject()
{
    GameObject* closestGO = nullptr;
    for (GameObject* obj : activeGameObjects) {
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
        activeGameObjects.erase(std::remove(activeGameObjects.begin(), activeGameObjects.end(), closestGO));
        delete closestGO;
        closestGO = nullptr;
    }
}

RectangleCollider** Stage::ReturnCollisions(RectangleCollider* colToCheck)
{
    RectangleCollider** colliders = frameAllocator.AllocArray<RectangleCollider*>(GameObject::sRectangleColliderPool.GetSize());
    int nextIndex = 0;
    if (colliders != nullptr) {
        for (int i = 0; i < GameObject::sRectangleColliderPool.GetSize(); i++) {
            if (colToCheck->CheckCollision(GameObject::sRectangleColliderPool.GetPoolArrayItem(i)) &&
                colToCheck != GameObject::sRectangleColliderPool.GetPoolArrayItem(i)) {
                colliders[nextIndex] = GameObject::sRectangleColliderPool.GetPoolArrayItem(i);
                nextIndex++;
            }
        }
    }
    std::string printString = "Num of collisions with checked collider: " + std::to_string(nextIndex);
    std::cout << printString << std::endl;
    return colliders;
}
