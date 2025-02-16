#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "SDL_rect.h"
#include "SDL_render.h"

class GameObject {
public:
  GameObject();
  ~GameObject();

  int speed;
  SDL_Point position;
  SDL_Point velocity;
  SDL_Point size;
  SDL_Texture *sprite;

  SDL_Rect *getRenderRect(void);
  void update(void);
  void move(SDL_Rect *boundaries);

protected:
  SDL_Rect renderRect;
};

#endif
