#include <SDL.h>

#include "SDL_render.h"
#include "game_object.h"

GameObject::GameObject() {
  position.x = 0;
  position.y = 0;
  velocity.x = 1;
  velocity.y = 1;
  size.x = 50;
  size.y = 50;
  speed = 1;
}

GameObject::~GameObject() {
  SDL_DestroyTexture(sprite);
  sprite = NULL;
}

SDL_Rect *GameObject::getRenderRect(void) {
  renderRect.x = position.x;
  renderRect.y = position.y;
  renderRect.w = size.x;
  renderRect.h = size.y;
  return &renderRect;
}

void GameObject::move(SDL_Rect *boundaries) {
  int lowerBound = boundaries->h - size.x;
  int rightBound = boundaries->w - size.y;

  position.x += velocity.x;
  position.y += velocity.y;

  if (position.x >= rightBound)
    position.x = rightBound;
  if (position.x < 0)
    position.x = 0;
  if (position.y >= lowerBound)
    position.y = lowerBound;
  if (position.y < 0)
    position.y = 0;
}

bool GameObject::checkCollision(GameObject *other) {
    // Calculate the sides of rect A
    int leftA = this->position.x;
    int rightA = this->position.x + this->size.x;
    int topA = this->position.y;
    int bottomA = this->position.y + this->size.y;

    //Calculate the sides of rect B
    int leftB = other->position.x;
    int rightB = other->position.x + other->size.x;
    int topB = other->position.y;
    int bottomB = other->position.y + other->size.y;

    if (bottomA <= topB || topA >= bottomB ||
        rightA <= leftB || leftA >= rightB)
        return false;

    //If none of the sides from A are outside B
    return true;
}
