#include <iostream>
#include <SDL.h>
#include "Renderer.h"
#include <vector>
#include <map>
#include "../entities/GameObject.h"
#include "../core/ManagerHub.h"
#include "SDL2/SDL_render.h"

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

void UpdateRenderer(SDL_Renderer* renderer, const int fps) {
    //Move to InitializeRenderer() to avoid unnecessary calculations
    const int framedelay = 1000 / fps;

    ManagerHub* managerHub = &ManagerHub::GetInstance();
    float delta_time = managerHub->timeManager->GetDeltaTime();

    SDL_RenderClear(renderer);

    for (auto& [pos_z, gameObjects]: managerHub->entityManager->visible_objects) {
        for (auto* game_object: gameObjects) {
            if (!game_object->flip_texture) {
                SDL_RenderCopy(renderer, game_object->texture, nullptr, &game_object->rect);
            }
            else {
                if (game_object->flip_mode == FLIP_HORIZONTAL) {
                    SDL_RenderCopyEx(renderer, game_object->texture, nullptr, &game_object->rect, 0, nullptr, SDL_FLIP_HORIZONTAL);
                }
                else if (game_object->flip_mode == FLIP_VERTICAL) {
                    SDL_RenderCopyEx(renderer, game_object->texture, nullptr, &game_object->rect, 0, nullptr, SDL_FLIP_VERTICAL);
                }
            }
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
