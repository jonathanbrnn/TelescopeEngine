#include <iostream>
#include <SDL.h>
#include "Renderer.h"
#include <vector>
#include <map>
#include "../entities/GameObject.h"
#include "../core/ManagerHub.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_timer.h"

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

SDL_Renderer* InitializeRenderer(SDL_Window* window, bool use_vsync) {
    SDL_Renderer* renderer = NULL;

    if (!window) {
        printf("Window was not created properly!");
    }
    else {
        if (use_vsync) { renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); }
        else { renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); }

        if (!renderer) {
            printf("Renderer could not not be created! SDL_Error: %s\n", SDL_GetError());
        }
    }

    return renderer;
}

void UpdateRenderer() {
    ManagerHub* managerHub = &ManagerHub::GetInstance();
    float delta_time = managerHub->timeManager->GetDeltaTime();

    SDL_Renderer* renderer = managerHub->contextManager->GetRenderer();

    int frame_delay = 1000 / managerHub->contextManager->GetTargetFramerate();

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

    if (!managerHub->contextManager->GetVsync()) {
        SDL_Delay(frame_delay);
    }
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
