#include "playercontroller.h"
#include <SDL.h>
#include "gameobject.h"

void PlayerController::Update(GameObject* playerobj, float dt)
{
    // VERTICAL
    if (keyboard[SDL_SCANCODE_W]) {
        player->transform.position.y -= dt;
    }
    else if (keyboard[SDL_SCANCODE_S]) {
        player->transform.position.y += dt;
    }

    // HORIZONTAL
    if (keyboard[SDL_SCANCODE_A]) {
        player->transform.position.x -= dt;
    }
    else if (keyboard[SDL_SCANCODE_D]) {
        player->transform.position.x += dt;
    }
}
