#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "rendering/Renderer.h"
#include "entities/GameObject.h"
#include <vector>


void closeEngine(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main() {
    SDL_Window* window = InitializeWindow(1920, 1080); 
    SDL_Renderer* renderer = InitializeRenderer(window); 

    GameObject gm1; 
    GameObject gm2; 

    gm1.InitializeGameObject(renderer); 
    gm2.InitializeGameObject(renderer, 100, 100);

    vector<GameObject> gameObjects; 

    gameObjects.push_back(gm1); 
    gameObjects.push_back(gm2); 

    UpdateRenderer(renderer, gameObjects);

    closeEngine(window, renderer);

    return 0; 
}