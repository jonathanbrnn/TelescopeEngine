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

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true; 
                break;
            }
            managerHub.inputManager->UpdateInput(event);
        }

        for (auto gameObject : managerHub.entityManager->total_objects) {
            gameObject->UpdateGameObject();
        }

        managerHub.timeManager->UpdateTime();
        managerHub.collisionManager->ProcessCollisions(); 
        UpdateRenderer(renderer); 
    }
}
