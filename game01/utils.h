#ifndef UTILS_H
#define UTILS_H

#include "SDL_render.h"

class Utils {
public:
  static SDL_Texture *loadTexture(const char *path, SDL_Renderer *renderer);
};

#endif
