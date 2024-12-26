#include <iostream>
#include <SDL.h>
#include "Renderer.h"
#include <vector>
#include "../entities/GameObject.h"

using namespace std; 

SDL_Window* InitializeWindow(int screenWidth, int screenHeight, int windowPositionX, int windowPositionY, const string& windowTitle) {
    SDL_Window* window = NULL;

    if (SDL_INIT_VIDEO < 0) {
        printf("SDL could not initilize! SDL_Error: %s\n", SDL_GetError()); 
    }
    else {
        window = SDL_CreateWindow(windowTitle.c_str(), windowPositionX, windowPositionY, screenWidth, screenHeight, SDL_WINDOW_SHOWN); 
        
        if(!window) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError()); 
        }
    }

    return window; 
}

SDL_Renderer* InitializeRenderer(SDL_Window* window) {
    SDL_Renderer* renderer = NULL; 

    if (!window) {
        printf("Window was not created properly!"); 
    } 
    else {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); 

        if (!renderer) {
            printf("Renderer could not not be created! SDL_Error: %s\n", SDL_GetError()); 
        }
    }

    return renderer; 
}

void UpdateRenderer(SDL_Renderer* renderer, vector<GameObject> gameObjects, const int fps) {
    const int framedelay = 1000 / fps; 

    bool quit = false; 
    SDL_Event event; 

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true; 
            }
        }

        SDL_RenderClear(renderer);

        for (auto& gameObject: gameObjects) {
            SDL_RenderCopy(renderer, gameObject.texture, nullptr, &gameObject.rect);
        }

        SDL_Delay(framedelay); 
    }
}