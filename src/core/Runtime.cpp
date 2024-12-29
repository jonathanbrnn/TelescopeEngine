#include <SDL.h>
#include <vector>
#include <map>
#include "Runtime.h"
#include "../input/InputManager.h"
#include "../rendering/Renderer.h"
#include "../entities/GameObject.h"


void Update(SDL_Renderer* renderer, map<int, vector<GameObject*>>& gameObjects) {
    bool quit = false; 
    SDL_Event event; 

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true; 
            }
            else if (ListenForInput(event)) {
                printf("KEY PRESSED: %d\n", event.key.keysym.sym); 
            }
        }

        UpdateRenderer(renderer, gameObjects); 
    }
}