#include <SDL2/SDL_log.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>

#include "../include/core/console.h"

SDL_Texture* console_texture_create(SDL_Window** window, SDL_Renderer** renderer, SDL_Surface** consoleSurface) {
  SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "! ----------- INITIALIZING CONSOLE -----------\n");

  if(!consoleSurface || !*consoleSurface) {
    SDL_LogError(SDL_LOG_CATEGORY_RENDER, "create::CONSOLE_SURFACE... INVALID | SDL::ERR -> %s\n", SDL_GetError());
    return NULL;
  } else {
    SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "create::CONSOLE_SURFACE... ok\n");
  }
  
  SDL_Texture* consoleTexture = SDL_CreateTextureFromSurface(*renderer, *consoleSurface);
  if (!consoleTexture) {
      SDL_LogError(SDL_LOG_CATEGORY_RENDER, "create::CONSOLE_TEXTURE... FAILED | SDL::ERR -> %s\n", SDL_GetError());
      return NULL;
  }

  return consoleTexture;
}
