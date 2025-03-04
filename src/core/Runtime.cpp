#include <SDL.h>
#include <vector>
#include <map>
#include <chrono>
#include "Runtime.h"
#include "ManagerHub.h"
#include "EntityManager.h"
#include "../demo/Player.h"
#include "../input/InputManager.h"
#include "../rendering/Renderer.h"
#include "../entities/GameObject.h"
#include "../entities/CollisionManager.h"

using namespace std; 

void UpdateAll(SDL_Renderer* renderer) {
    bool quit = false; 
    SDL_Event event; 

    ManagerHub& managerHub = ManagerHub::GetInstance(); 

    GameObject* player = managerHub.entityManager->FindGameObjectByName("Jonathan");
    // GameObject* player = new GameObject(renderer, "A", 100, 0, 1000, 100, 100, 0, "../media/D5A7C13D-BA69-41D6-9BD7-B1DD66045837_4_5005_c Background Removed.png"); 

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true; 
            }
            else if (ListenForInput(event)) {
                KeyPress keyPress = HandleKeyPress(event.key.keysym.sym);
                MovePlayer(player, keyPress);
                /*
                if (keyPress == KEY_PRESS_SPACE) {
                    managerHub.entityManager->Instantiate("Enemy", player->rect.x + (player->width / 2), player->rect.y + (player->height / 2), player->pos_z, player->body->dx * 10.0f + 10.0f, player->body->dy * 10.0f + 10.0f); 
                }
                */
                break; 
            }
        }

        for (auto gameObject : managerHub.entityManager->total_objects) {
            gameObject->UpdateGameObject();
        }

        managerHub.timeManager->UpdateTime();
        managerHub.collisionManager->ProcessCollisions(); 
        UpdateRenderer(renderer); 
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
            player->Whisper(1);
            break; 
        case KEY_PRESS_ONE: 
            player->Whisper(2);
        case KEY_PRESS_TWO:
            break;
        case KEY_PRESS_THREE: 
            EntityManager::GetInstance().FindGameObjectByName("Celestine")->Whisper(1);
        default: 
            player->body->base_dx = 0; 
            player->body->base_dy = 0;
            break; 
    }    
}