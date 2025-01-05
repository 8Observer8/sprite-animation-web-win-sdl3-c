#define SDL_MAIN_USE_CALLBACKS 1 // Use the callbacks instead of main()
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

// We will use this renderer to draw into this window every frame
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;

int frameIndex = 0;
uint32_t lastTickTime = 0;
float animationTime = 0.f;
const float animationPeriod = 0.1f;

// Define animation frames (adjust dimensions and positions as needed)
SDL_FRect frames[4] = {
    { 0, 0, 128, 128 }, // Frame 1
    { 128, 0, 128, 128 }, // Frame 2
    { 0, 128, 128, 128 }, // Frame 3
    { 128, 128, 128, 128 }  // Frame 4
};

// This function runs once at startup
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Sprite animation using SDL3 and C",
        350, 350, 0, &window, &renderer)) //
    {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_SetRenderVSync(renderer, 1);

    const char *texturePath = "./assets/sprites/spritesheet.png";
    texture = IMG_LoadTexture(renderer, texturePath);
    if (!texture) {
        SDL_Log("Couldn't load %s: %s\n", texturePath, SDL_GetError());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE; // Carry on with the program!
}

// This function runs when a new event (mouse input, keypresses, etc) occurs
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS; // End the program, reporting success to the OS
    }
    return SDL_APP_CONTINUE; // Carry on with the program!
}

// This function runs once per frame, and is the heart of the program
SDL_AppResult SDL_AppIterate(void *appstate)
{
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE); // Canvas color
    SDL_RenderClear(renderer); // Clear the canvas and fill it with the canvas color

    // Update and render animation
    SDL_FRect srcRect = frames[frameIndex];
    SDL_FRect destRect = { 0, 0, 128, 128 }; // Adjust x, y for positioning

    // Render the current frame
    SDL_RenderTexture(renderer, texture, &srcRect, &destRect);

    SDL_RenderPresent(renderer);

    // Calculate dt
    uint32_t currentTickTime = SDL_GetTicks();
    float deltaTime = (currentTickTime - lastTickTime) / 1000.f;
    lastTickTime = currentTickTime;

    // Animation time
    animationTime += deltaTime;

    // Increment frame index and loop back to 0 when necessary
    if (animationTime > animationPeriod) {
        frameIndex = (frameIndex + 1) % 4;
        animationTime = 0.f;
    }

    return SDL_APP_CONTINUE; // Carry on with the program!
}

// This function runs once at shutdown
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    // SDL will clean up the window/renderer for us
}
