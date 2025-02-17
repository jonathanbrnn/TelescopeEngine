#include <SDL.h>
#include <vector>
#include <map>
#include <chrono>
#include "Runtime.h"
#include "EntityManager.h"
#include "../input/InputManager.h"
#include "../rendering/Renderer.h"
#include "../entities/GameObject.h"
#include "../entities/CollisionManager.h"

using namespace std; 


void Update(SDL_Renderer* renderer, EntityManager& entityManager, CollisionManager& collisionManager) {
    auto originalTime = chrono::high_resolution_clock::now(); 
    
    bool quit = false; 
    SDL_Event event; 

    GameObject* player = entityManager.FindGameObjectByName("Enemy");
    // GameObject* player = new GameObject(renderer, "A", 100, 0, 1000, 100, 100, 0, "../media/D5A7C13D-BA69-41D6-9BD7-B1DD66045837_4_5005_c Background Removed.png"); 
    
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
                KeyPress keyPress = HandleKeyPress(event.key.keysym.sym);
                MovePlayer(player, keyPress);

                if (keyPress == KEY_PRESS_SPACE) {
                    entityManager.Instantiate("Enemy", player->rect.x + (player->w / 2), player->rect.y + (player->h / 2), player->posZ, player->dx * 10.0f + 10.0f, player->dy * 10.0f + 10.0f); 
                }
                break; 
            }
        }

        collisionManager.ProcessCollisions(); 
        UpdateRenderer(renderer, entityManager.active_gameObjects, deltaTime); 
    }
}

void MovePlayer(GameObject* player, KeyPress key) { 
    switch(key) {
        case KEY_PRESS_LEFT: 
            player->dx = -3; 
            break; 
        case KEY_PRESS_RIGHT: 
            player->dx = 3; 
            break; 
        case KEY_PRESS_UP: 
            player->dy = -3; 
            break; 
        case KEY_PRESS_DOWN: 
            player->dy = 3; 
            break; 
        case KEY_PRESS_SPACE: 
            break; 
        case KEY_PRESS_ONE: 
            player->forces.clear();
            player->ApplyForce(1, 5, LINEAR);  
        case KEY_PRESS_TWO:
            player->forces.clear(); 
            player->ApplyForce(-1, 3, QUADRATIC_EASE_IN); 
        case KEY_PRESS_THREE: 
            player->forces.clear(); 
            player->ApplyForce(1, 3, QUADRATIC_EASE_OUT);
        default: 
            player->SetVelocity(0, 0); 
            break; 
    }    
}