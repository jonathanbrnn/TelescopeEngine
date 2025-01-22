#include <SDL.h>
#include <vector>
#include <map>
#include <chrono>
#include "Runtime.h"
#include "EntityManager.h"
#include "../input/InputManager.h"
#include "../rendering/Renderer.h"
#include "../entities/GameObject.h"

using namespace std; 


void Update(SDL_Renderer* renderer, EntityManager& entityManager) {
    auto originalTime = chrono::high_resolution_clock::now(); 
    
    bool quit = false; 
    SDL_Event event; 

    GameObject* player = new GameObject(renderer, "A", 0, 0, 1000, 100, 100, 0, "../media/D5A7C13D-BA69-41D6-9BD7-B1DD66045837_4_5005_c Background Removed.png"); 
    entityManager.active_gameObjects[1000].push_back(player); 
    player->SetVelocity(0, 0);

    while (!quit) {
        auto currentTime = chrono::high_resolution_clock::now(); 
        chrono::duration<float> elapsedTime = currentTime - originalTime; 
        float deltaTime = elapsedTime.count(); 
        originalTime = currentTime;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true; 
            }
            else if (ListenForInput(event)) {
                MovePlayer(player, HandleKeyPress(event.key.keysym.sym));
                cout << player->dx << " " << player->dy << endl; 
                break; 
            }
        }

        UpdateRenderer(renderer, entityManager.active_gameObjects, deltaTime); 
    }
}

void MovePlayer(GameObject* player, KeyPress key) { 
    switch(key) {
        case KEY_PRESS_LEFT: 
            player->dx = -10; 
            break; 
        case KEY_PRESS_RIGHT: 
            player->dx = 10; 
            break; 
        case KEY_PRESS_UP: 
            player->dy = -10; 
            break; 
        case KEY_PRESS_DOWN: 
            player->dy = 10; 
            break; 
        case KEY_PRESS_DEFAULT: 
            player->SetVelocity(0, 0); 
            break; 
    }    
}