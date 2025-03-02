#include <SDL.h>
#include <vector>
#include <map>
#include <chrono>
#include "Runtime.h"
#include "ManagerHub.h"
#include "EntityManager.h"
#include "../input/InputManager.h"
#include "../rendering/Renderer.h"
#include "../entities/GameObject.h"
#include "../entities/CollisionManager.h"

using namespace std; 

void Update(SDL_Renderer* renderer) {
    auto originalTime = chrono::high_resolution_clock::now(); 
    
    bool quit = false; 
    SDL_Event event; 

    ManagerHub& managerHub = ManagerHub::GetInstance(); 

    GameObject* player = managerHub.entityManager->FindGameObjectByName("Enemy");
    // GameObject* player = new GameObject(renderer, "A", 100, 0, 1000, 100, 100, 0, "../media/D5A7C13D-BA69-41D6-9BD7-B1DD66045837_4_5005_c Background Removed.png"); 
    
    player->body->SetVelocity(0, 0);

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
                    managerHub.entityManager->Instantiate("Enemy", player->rect.x + (player->width / 2), player->rect.y + (player->height / 2), player->pos_z, player->body->dx * 10.0f + 10.0f, player->body->dy * 10.0f + 10.0f); 
                }
                break; 
            }
        }

        managerHub.collisionManager->ProcessCollisions(); 
        UpdateRenderer(renderer, deltaTime); 
    }
}

void MovePlayer(GameObject* player, KeyPress key) { 
    switch(key) {
        case KEY_PRESS_LEFT: 
            player->body->base_dx = -3; 
            break; 
        case KEY_PRESS_RIGHT: 
            player->body->base_dx = 3; 
            break; 
        case KEY_PRESS_UP: 
            player->body->base_dy = -3; 
            break; 
        case KEY_PRESS_DOWN: 
            player->body->base_dy = 3; 
            break; 
        case KEY_PRESS_SPACE: 
            break; 
        case KEY_PRESS_ONE: 
            player->body->forces.clear();
            player->body->ApplyForce(1, 50, LINEAR);  
        case KEY_PRESS_TWO:
            player->body->forces.clear(); 
            player->body->ApplyForce(-1, 3, QUADRATIC_EASE_IN); 
        case KEY_PRESS_THREE: 
            player->body->forces.clear(); 
            player->body->ApplyForce(1, 3, QUADRATIC_EASE_OUT);
        default: 
            player->body->SetVelocity(0, 0); 
            break; 
    }    
}