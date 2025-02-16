#include <SDL.h>
#include <SDL_image.h>

#include "utils.h"

SDL_Texture *Utils::loadTexture(const char *path, SDL_Renderer *renderer) {
  SDL_Texture *texture = NULL;
  SDL_Surface *image = IMG_Load(path);

  if (image == NULL)
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Couldn't load asset at %s! SDL error: %s", path,
                 SDL_GetError());

  texture = SDL_CreateTextureFromSurface(renderer, image);
  if (texture == NULL)
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Couldn't create texture from %s! SDL error: %s", path,
                 SDL_GetError());

  SDL_FreeSurface(image);
  return texture;
}
