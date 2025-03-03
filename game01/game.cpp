#include "SDL_image.h"
#include "game_object.h"
#include "player.h"
#include "utils.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <cstdlib>

// game lifecycle
bool init(void);
bool loadAssets(void);
void render(void);
void update(void);
void destroy(void);

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

// Global vars
SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
SDL_Texture *gBackgroundTexture = NULL;
TTF_Font *gFont = NULL;
SDL_Rect gViewport = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

Player player = Player();
GameObject apple = GameObject();
bool appleTaken = true;
int score = 0;

int main(int argc, char *argv[]) {
  if (!(init() && loadAssets())) {
    return 1;
  }

  SDL_Event e;
  bool quit = false;

  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }
    update();
    render();
  }

  destroy();

  return 0;
}

void update(void) {
  if (apple.checkCollision(&player)) {
      appleTaken = true;
  }

  if (appleTaken) {
    score += 1;
    apple.position.x = std::rand() % (SCREEN_WIDTH - apple.size.x);
    apple.position.y = std::rand() % (SCREEN_HEIGHT - apple.size.y);
    appleTaken = false;
  }

  player.update();
  player.move(&gViewport);
}

void render(void) {
  // Clear
  SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
  SDL_RenderClear(gRenderer);

  // Draw
  SDL_RenderCopy(gRenderer, gBackgroundTexture, NULL, NULL);
  SDL_RenderCopy(gRenderer, player.sprite, NULL, player.getRenderRect());
  SDL_RenderCopy(gRenderer, apple.sprite, NULL, apple.getRenderRect());


  // Render back buffer
  SDL_RenderPresent(gRenderer);
}

bool init(void) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s",
                 SDL_GetError());
    return false;
  }
  gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                             SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (gWindow == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Couldn't create window! SDL error: %s", SDL_GetError());
    return false;
  }

  gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
  if (gRenderer == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Couldn't create render! SDL error: %s", SDL_GetError());
    return false;
  }

  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) && imgFlags)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "SDL_image could not initialize! SDL error: %s",
                 IMG_GetError());
    return false;
  }

  return true;
}

bool loadAssets(void) {
  gBackgroundTexture = Utils::loadTexture("../assets/texture.jpg", gRenderer);
  if (gBackgroundTexture == NULL)
    return false;

  SDL_Texture *playerTexture =
      Utils::loadTexture("../assets/player.png", gRenderer);
  if (playerTexture == NULL)
    return false;
  player.sprite = playerTexture;

  SDL_Texture *appleTexture =
      Utils::loadTexture("../assets/apple.png", gRenderer);
  if (appleTexture == NULL)
    return false;
  apple.sprite = appleTexture;

  return true;
}

void destroy(void) {
  SDL_DestroyTexture(gBackgroundTexture);
  gBackgroundTexture = NULL;

  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  gRenderer = NULL;

  IMG_Quit();
  SDL_Quit();
}
