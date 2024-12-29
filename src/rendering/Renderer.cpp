#include <iostream>
#include <SDL.h>
#include "Renderer.h"
#include <vector>
#include <map>
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
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); 

        if (!renderer) {
            printf("Renderer could not not be created! SDL_Error: %s\n", SDL_GetError()); 
        }
    }

    return renderer; 
}

void UpdateRenderer(SDL_Renderer* renderer, map<int, vector<GameObject*>>& gameObjects, const int fps) {
    const int framedelay = 1000 / fps; 

    SDL_RenderClear(renderer);

    for (auto& [z, curr_gameObjects]: gameObjects) {
        for (auto* gm: curr_gameObjects) {
            gm->UpdateVelocity(); 
            SDL_RenderCopy(renderer, gm->texture, nullptr, &gm->rect); 
        }
    }


    SDL_RenderPresent(renderer); 
    // SDL_Delay(framedelay); - Currently using VSYNC
}

/*
This is the old code for the dvd logo example: 

for (auto& gameObject: gameObjects) {
        gameObject.rect.x += gameObject.dx; 
        gameObject.rect.y += gameObject.dy; 

        if (gameObject.rect.x <= 0 || gameObject.rect.x + gameObject.rect.w >= 1920) {
            gameObject.dx = -gameObject.dx; // Reverse horizontal direction
        }

        if (gameObject.rect.y <= 0 || gameObject.rect.y + gameObject.rect.h >= 1080) {
            gameObject.dy = -gameObject.dy; // Reverse vertical direction
        }

        SDL_RenderCopy(renderer, gameObject.texture, nullptr, &gameObject.rect);
    }

*/