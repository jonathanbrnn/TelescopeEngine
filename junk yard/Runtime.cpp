#include "Runtime.h"

using namespace std;

void UpdateAll(SDL_Renderer* renderer) {
    bool quit = false;
    SDL_Event event;

    ManagerHub* managerHub = &ManagerHub::GetInstance();

    //managerHub->contextManager->OnStart();

    while (!quit) {
        managerHub->inputManager->ResetIsPressed();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
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

        UpdateRenderer(renderer);

        managerHub->entityManager->DeleteObjects();
    }
}
