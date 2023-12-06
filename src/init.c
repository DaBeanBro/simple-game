// init.c
#include <SDL2/SDL.h>
#include <stdbool.h>

// Project defined headers
#include "../include/core/init.h"

// Screen dimentions
const uint16_t SCREEN_WIDTH = 640;
const uint16_t SCREEN_HEIGHT = 480;
// Initialization function for SDL window and renderer
bool game_init(SDL_Window** window, SDL_Renderer** renderer) {
    // Create window
    *window = SDL_CreateWindow("Doom Style FPS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (*window == NULL) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "create::WINDOW... FAILED | SDL::ERR -> %s\n", SDL_GetError());

        return false;
    }

    // Create renderer
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "create::RENDERER... FAILED | SDL::ERR -> %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);                                         

        return false;
    }

    return true; // Initialization successful
}
