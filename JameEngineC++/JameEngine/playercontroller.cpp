#include "playercontroller.h"

#include <SDL.h>
#include "gameobject.h"

PlayerController::PlayerController()
{
    type = 2;
    parentGO = nullptr;
}

PlayerController::PlayerController(GameObject* obj, float moveSpeed)
{
    type = 2;
    parentGO = obj;
    speed = moveSpeed;
}

void PlayerController::Update(float dt)
{
    const Uint8* keyboard = SDL_GetKeyboardState(NULL);

    // VERTICAL
    if (keyboard[SDL_SCANCODE_UP]) {
        parentGO->transform.position.y -= dt * speed;
    }
    else if (keyboard[SDL_SCANCODE_DOWN]) {
        parentGO->transform.position.y += dt * speed;
    }

    // HORIZONTAL
    if (keyboard[SDL_SCANCODE_LEFT]) {
        parentGO->transform.position.x -= dt * speed;
    }
    else if (keyboard[SDL_SCANCODE_RIGHT]) {
        parentGO->transform.position.x += dt * speed;
    }
}
