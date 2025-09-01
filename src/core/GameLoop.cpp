#include "GameLoop.h"

void GameLoop::UpdateCore() {
    running = true; 
    managerHub = &ManagerHub::GetInstance(); 
    SDL_Event event;
    
    while (running) {
        managerHub->inputManager->ResetIsPressed(); 

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                break;
            }
            
            managerHub->inputManager->UpdateInputManager(event); 
        }

        managerHub->timeManager->UpdateTime();

        managerHub->entityManager->PushNewObjects();

        for (auto gameObject : managerHub->entityManager->total_objects) {
            gameObject->UpdateGameObject();
        }

        managerHub->collisionManager->ProcessCollisions();

        managerHub->renderer->UpdateRenderer(); 

        managerHub->entityManager->DeleteObjects(); 
    }
}