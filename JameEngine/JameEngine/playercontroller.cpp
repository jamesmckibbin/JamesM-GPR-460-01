#include "playercontroller.h"
#include <SDL.h>
#include "gameobject.h"

PlayerController::PlayerController(GameObject* obj, float moveSpeed)
{
    parentGO = obj;
    speed = moveSpeed;
}

void PlayerController::Update(float dt)
{
    const Uint8* keyboard = SDL_GetKeyboardState(NULL);

    // VERTICAL
    if (keyboard[SDL_SCANCODE_W]) {
        parentGO->transform.position.y -= dt * speed;
    }
    else if (keyboard[SDL_SCANCODE_S]) {
        parentGO->transform.position.y += dt * speed;
    }

    // HORIZONTAL
    if (keyboard[SDL_SCANCODE_A]) {
        parentGO->transform.position.x -= dt * speed;
    }
    else if (keyboard[SDL_SCANCODE_D]) {
        parentGO->transform.position.x += dt * speed;
    }
}
