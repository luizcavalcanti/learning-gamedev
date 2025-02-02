#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <stdio.h>

// game lifecycle
bool init(void);
bool loadAssets(void);
void destroy(void);

void processInput(void);
void render(void);
void update(void);

// assets management
SDL_Surface *loadSurface(const char *path);
SDL_Texture *loadTexture(const char *path);

// Types
typedef struct {
    float x;
    float y;
} position;

typedef struct {
    float w;
    float h;
} size;

typedef struct {
    float h;
    float v;
} velocity;

typedef struct {
    velocity vel;
    position pos;
    size size;
    SDL_Texture *sprite;
} object;


const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

// Global vars
SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
SDL_Texture *gBackgroundTexture = NULL;
object player = {
    .size = { 50, 50 },
    .pos = { 0, 0 },
    .vel = { 1.5f, 1.5f }
};


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

void update(void) {
    int lowerBound = SCREEN_HEIGHT - player.size.h;
    int rightBound = SCREEN_WIDTH - player.size.w;
    if (player.pos.x >= rightBound)
        player.pos.x = rightBound;
    if (player.pos.x < 0)
        player.pos.x = 0;
    if (player.pos.y >= lowerBound)
        player.pos.y = lowerBound;
    if (player.pos.y < 0)
        player.pos.y = 0;
}

void render(void) {
    // Clear
    SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(gRenderer);

    // Draw
    SDL_RenderCopy(gRenderer, gBackgroundTexture, NULL, NULL);
    SDL_Rect playerPos = { player.pos.x, player.pos.y, player.size.w, player.size.h };
    SDL_RenderCopy(gRenderer, player.sprite, NULL, &playerPos);

    // Render back buffer
    SDL_RenderPresent(gRenderer);
}

void processInput(void) {
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_UP])
        player.pos.y -= player.vel.v;
    if (currentKeyStates[SDL_SCANCODE_DOWN])
        player.pos.y += player.vel.v;
    if (currentKeyStates[SDL_SCANCODE_LEFT])
        player.pos.x -= player.vel.h;
    if (currentKeyStates[SDL_SCANCODE_RIGHT])
        player.pos.x += player.vel.h;
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
    gBackgroundTexture = loadTexture("../assets/texture.jpg");
    if (gBackgroundTexture == NULL)
        return false;

    SDL_Texture *playerTexture = loadTexture("../assets/player.png");
    if (playerTexture == NULL)
        return false;
    player.sprite = playerTexture;

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

SDL_Texture *loadTexture(const char *path) {
    SDL_Texture *texture = NULL;
    SDL_Surface *image = IMG_Load(path);

    if (image == NULL)
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load asset at %s! SDL error: %s", path, SDL_GetError());

    texture = SDL_CreateTextureFromSurface(gRenderer, image);
    if (texture == NULL)
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from %s! SDL error: %s", path, SDL_GetError());

    SDL_FreeSurface(image);
    return texture;
}
