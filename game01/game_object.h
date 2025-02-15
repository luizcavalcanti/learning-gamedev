#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SDL.h>
#include <SDL_image.h>

class GameObject {
 public:
    GameObject();

    SDL_Rect *getRenderRect();

    SDL_Point position;
    SDL_Point velocity;
    SDL_Point size;
    SDL_Texture *sprite;

 private:
    SDL_Rect renderRect;
};

#endif
