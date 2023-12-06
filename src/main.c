// main.c
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

// Project defined headers
#include "../include/core/types.h"
#include "../include/core/init.h"

// Macros
#define ENABLE_FPS_LOGGING 0  // Option to enable fps logging
#define ENABLE_FPS_LIMIT 1 // Option for toggling 60fps
                              
// Variables for FPS calculation
static u32 frameCount = 0;
static u32 lastTime = 0;
static f32 fps = 0.0f;
const u8 FPS_CAP = 60;
const i32 FRAME_DELAY = 1000 / FPS_CAP;  // Time for each frame in milliseconds

// Fps logging function
void updateFPS() {
    frameCount++;
    u32 currentTime = SDL_GetTicks();

    // Calculate fps every second
    if (currentTime > lastTime + 1000) {
        fps = frameCount / ((currentTime - lastTime) / 1000.0f);
        frameCount = 0;
        lastTime = currentTime;

        #if ENABLE_FPS_LOGGING
        SDL_Log("FPS: %.2f", fps);
        #endif
    }
}
                                      
// Main function
int main(int argc, char* args[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Surface* screenSurface = NULL;

    // Set priority of the game
    // use: 
    //      allows me to see debug logs
    SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG);
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);

    // Initialize SDL
    SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "! ----------- INITIALIZING SDL -----------\n");

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "init::SDL... FAILED | SDL::ERR -> %s\n", SDL_GetError());
        SDL_Quit();
        SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "terminated::SDL... ok\n"); 
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Exiting...\n");

        return 1;
    }

    // --- Initialize game ---
    if (!game_init(&window, &renderer)) {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "\n\n! ----------- Failed to initialise Game -----------\n"); 
        SDL_Quit();
        SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "terminated::SDL... ok\n");
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Exiting...\n");

        return 2;
    } 

    // Setup
    u32 frameStart;
    i32 frameTime;
    bool running = true;
    SDL_Event e;

    // Main game loop
    while (running) {
    frameStart = SDL_GetTicks();
        // Main event loop
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
            // Additional event handling here
        }

        // --- Game rendering ---
        // Clear the renderer
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Set the draw color
        SDL_SetRenderDrawColor(renderer, 210, 230, 40, 255);

        // Draw a rectangle
        SDL_Rect myRect = { 320, 240, 100, 100 };
        
        // --- Rendering logic ---
        SDL_RenderFillRect(renderer, &myRect);
        SDL_RenderPresent(renderer);

        // Update FPS
         #if ENABLE_FPS_LIMIT
        frameTime = SDL_GetTicks() - frameStart;
        if (FRAME_DELAY > frameTime) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
        #endif
        updateFPS();
    }
    
    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "destroying::RENDERER... ok\n");
    SDL_DestroyWindow(window);
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "destroying::WINDOW... ok\n");
    SDL_FreeSurface(screenSurface);
    SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "destroying::SURFACE... ok\n");
    SDL_Quit();
    SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "terminated::SDL... ok\n");

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "All contexts and processes have succesfully been terminated!\n\n");

    // Bye
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Exiting... Bye :D\n");

    return 0;
}
