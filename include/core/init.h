#ifndef INIT_H
#define INIT_H
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <sys/types.h>

// Globals
// Screen dimensions
extern const uint16_t SCREEN_WIDTH;
extern const uint16_t SCREEN_HEIGHT;

bool game_create_window(SDL_Window** window);
bool game_create_renderer(SDL_Window** window, SDL_Renderer** renderer);

#endif // INIT_H
