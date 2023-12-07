#ifndef CONSOLE_H
#define CONSOLE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

// Console
SDL_Texture* console_texture_create(SDL_Window** window, SDL_Renderer** renderer, SDL_Surface** consoleSurface);

// Console methods
int console_hello();
#endif // CONSOLE_H
