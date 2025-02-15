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
