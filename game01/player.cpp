#include <SDL.h>

#include "player.h"

void Player::update() {
  const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
  const int speed = 1;
  velocity.x = 0;
  velocity.y = 0;
  if (currentKeyStates[SDL_SCANCODE_UP])
    velocity.y = -speed;
  if (currentKeyStates[SDL_SCANCODE_DOWN])
    velocity.y = speed;
  if (currentKeyStates[SDL_SCANCODE_LEFT])
    velocity.x = -speed;
  if (currentKeyStates[SDL_SCANCODE_RIGHT])
    velocity.x = speed;
}
