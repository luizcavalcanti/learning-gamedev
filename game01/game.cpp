#include "SDL_render.h"
#include "SDL_video.h"

#include "game_object.h"
#include "utils.h"

// game lifecycle
bool init(void);
bool loadAssets(void);
void destroy(void);

void processInput(void);
void render(void);
void update(void);

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

// Global vars
SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
SDL_Texture *gBackgroundTexture = NULL;
SDL_Rect gViewport = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

GameObject player = GameObject();
GameObject enemy = GameObject();

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
        processInput();
        update();
        render();
    }

    destroy();

    return 0;
}

void processInput(void) {
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_UP])
        player.position.y -= player.velocity.y;
    if (currentKeyStates[SDL_SCANCODE_DOWN])
        player.position.y += player.velocity.y;
    if (currentKeyStates[SDL_SCANCODE_LEFT])
        player.position.x -= player.velocity.x;
    if (currentKeyStates[SDL_SCANCODE_RIGHT])
        player.position.x += player.velocity.x;
}

void update(void) {
    player.move(&gViewport);
}

void render(void) {
    // Clear
    SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(gRenderer);

    // Draw
    SDL_RenderCopy(gRenderer, gBackgroundTexture, NULL, NULL);
    SDL_RenderCopy(gRenderer, player.sprite, NULL, player.getRenderRect());
    SDL_RenderCopy(gRenderer, enemy.sprite, NULL, enemy.getRenderRect());

    // Render back buffer
    SDL_RenderPresent(gRenderer);
}

bool init(void) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return false;
    }
    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window! SDL error: %s", SDL_GetError());
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create render! SDL error: %s", SDL_GetError());
        return false;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) && imgFlags)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_image could not initialize! SDL error: %s", IMG_GetError());
        return false;
    }

    return true;
}

bool loadAssets(void) {
    gBackgroundTexture = Utils::loadTexture("../assets/texture.jpg", gRenderer);
    if (gBackgroundTexture == NULL)
        return false;

    SDL_Texture *playerTexture = Utils::loadTexture("../assets/player.png", gRenderer);
    if (playerTexture == NULL)
        return false;
    player.sprite = playerTexture;
    enemy.sprite = playerTexture;

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
