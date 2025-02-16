#include "game_object.h"
#include "SDL_rect.h"

GameObject::GameObject() {
    position.x = 0;
    position.y = 0;
    velocity.x = 1;
    velocity.y = 1;
    size.x = 50;
    size.y = 50;
}

SDL_Rect *GameObject::getRenderRect() {
  renderRect.x = position.x;
  renderRect.y = position.y;
  renderRect.w = size.x;
  renderRect.h = size.y;
  return &renderRect;
}

void GameObject::move(SDL_Rect *boundaries) {
    int lowerBound = boundaries->h - size.x;
    int rightBound = boundaries->w - size.y;
    if (position.x >= rightBound)
        position.x = rightBound;
    if (position.x < 0)
        position.x = 0;
    if (position.y >= lowerBound)
        position.y = lowerBound;
    if (position.y < 0)
        position.y = 0;
}
