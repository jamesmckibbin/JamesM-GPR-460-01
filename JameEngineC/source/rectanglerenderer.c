#include "rectanglerenderer.h"

void rectangle_renderer_init(rectangle_renderer_t *self, float new_width, float new_height, color_t new_color) {
    self->width = new_width;
    self->height = new_height;
    self->color = new_color;
}

void rectangle_renderer_update(rectangle_renderer_t *self, float dt) {
    // do nothing
}

void rectangle_renderer_draw(rectangle_renderer_t *self, SDL_Renderer *renderer) {
    SDL_Rect newRect;
    newRect.x = (int)(self->parent->transform.position.x - (self->width / 2));
    newRect.y = (int)(self->parent->transform.position.y - (self->height / 2));
    newRect.w = (int)self->width;
    newRect.h = (int)self->height;
    SDL_SetRenderDrawColor(renderer, (Uint8)self->color.r, (Uint8)self->color.g, (Uint8)self->color.b, (Uint8)self->color.a);
    SDL_RenderFillRect(renderer, &newRect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
