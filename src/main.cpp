#include <iostream>
#include <random>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "rendering/Renderer.h"

using namespace std;

enum KeyPress {
    KEY_PRESS_DEFAULT, 
    KEY_PRESS_LEFT,
    KEY_PRESS_RIGHT, 
    KEY_PRESS_UP, 
    KEY_PRESS_DOWN
};

KeyPress handleKeyPress(SDL_Keycode key) {
    switch (key) {
        case SDLK_w:
        case SDLK_UP: return KEY_PRESS_UP; 
        case SDLK_s: 
        case SDLK_DOWN: return KEY_PRESS_DOWN; 
        case SDLK_a:
        case SDLK_LEFT: return KEY_PRESS_LEFT; 
        case SDLK_d:
        case SDLK_RIGHT: return KEY_PRESS_RIGHT; 
        default: return KEY_PRESS_DEFAULT;  
    }
}

SDL_Window* createWindow(SDL_Renderer*& renderer, int screenWidth = 680, int screenHeight = 480, int windowPositionX = 0, int windowPositionY = 0, vector<int> screenSurfaceColor = {0, 0, 0}) {
    SDL_Window* window = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    } else {
        window = SDL_CreateWindow("TelescopeEngine", windowPositionX, windowPositionY, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
        if (!window) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        } else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (!renderer) {
                printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
            }
        }
    }

    return window;
}

void loadImage(SDL_Renderer*& renderer, const string& filepath) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, filepath.c_str());

    if (!texture) {
        printf("Could not load image! %s\n", IMG_GetError());
        return;
    }

    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
}

void closeEngine(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void runtime(SDL_Window* window, SDL_Renderer* renderer, int fps = 120) {
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    random_device rd; 
    mt19937 gen(rd()); 
    uniform_int_distribution<> dis(0, 255); 

    const int frameDelay = 1000 / fps;
    SDL_Event event;
    bool quit = false;

    int recX = windowWidth / 2; 
    int recY = windowHeight / 2;
    int speed = 10;  
    SDL_Rect rectangle = { recX, recY, 50, 50 };


    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN) {
                switch (handleKeyPress(event.key.keysym.sym)) {
                    case KEY_PRESS_UP:
                        printf("w\n");
                        recY -= speed; // Move up
                        break;
                    case KEY_PRESS_DOWN:
                        recY += speed; // Move down
                        break;
                    case KEY_PRESS_LEFT:
                        recX -= speed; // Move left
                        break;
                    case KEY_PRESS_RIGHT:
                        recX += speed; // Move right
                        break;
                    case KEY_PRESS_DEFAULT:
                        continue; // No action on other keys
                        break;
                }
            }
        }

        // Update the rectangle's position with the new values
        rectangle.x = recX;  // Update rectangle's x position
        rectangle.y = recY;  // Update rectangle's y position

        SDL_RenderClear(renderer);

        // Background
        SDL_SetRenderDrawColor(renderer, 10, 100, 1, 255);
        SDL_RenderFillRect(renderer, NULL);

        // Rectangle
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rectangle);

        SDL_RenderPresent(renderer);
        SDL_Delay(frameDelay);
    }

    closeEngine(window, renderer);
}

int main(int argc, char* args[]) {
    SDL_Renderer* renderer = NULL;
    SDL_Window* window = createWindow(renderer, 640, 426);

    loadImage(renderer, "/Users/jonathan/TelescopeEngine/media/sample_640×426.bmp");

    runtime(window, renderer);

    return 0;
}
