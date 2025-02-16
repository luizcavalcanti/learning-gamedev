#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "SDL_rect.h"
#include "SDL_render.h"

class GameObject {
public:
  GameObject();

  SDL_Rect *getRenderRect();
  void move(SDL_Rect *boundaries);

  SDL_Point position;
  SDL_Point velocity;
  SDL_Point size;
  SDL_Texture *sprite;

private:
  SDL_Rect renderRect;
};

#endif
