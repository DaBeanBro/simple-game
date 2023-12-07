#include "SDL2/SDL_events.h"
#include "SDL2/SDL_keyboard.h"
#include "SDL2/SDL_log.h"
#include <stdbool.h>
#include <SDL2/SDL.h>

const uint16_t WINDOW_WIDTH = 640;
const uint16_t WINDOW_HEIGHT = 480;

void game_clean(SDL_Window** window) {
  SDL_DestroyWindow(*window);
}

int sdl_init() {
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "init::SDL... FAILED\nSDL::ERR::%s\n", SDL_GetError());
    return 1;
  } else {
    SDL_LogInfo(SDL_LOG_CATEGORY_SYSTEM, "init::SDL... ok\n");
  }

  return 0;
}

SDL_Window* sdl_window_create() {
  SDL_Window* window = NULL;
  window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

  if(window == NULL) {
    SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "create::SDL_WINDOW... FAILED\nSDL::ERR::%s\n", SDL_GetError());
    return NULL;
  } else {
    SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "create::SDL_WINDOW... ok\n");
  }

  return window;
}

int main() {
  bool running = false;

  bool isInitialised = sdl_init();

  if(!isInitialised) {
    return 1;
  }

  SDL_Window* window = sdl_window_create();


  while(running) {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_KEYDOWN) {
        if(event.key.keysym.sym == SDLK_w) {
          game_clean(&window);
          SDL_LogInfo(SDL_LOG_CATEGORY_SYSTEM, "Bye!\n");
          return 0;
        }
      }
    }
  }

  SDL_Quit();
  return 0;
}
