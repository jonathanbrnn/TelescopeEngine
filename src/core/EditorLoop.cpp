#include "EditorLoop.h"

void EditorLoop::UpdateCore() {
    running = true; 
    managerHub = &ManagerHub::GetInstance(); 
    SDL_Event event; 

    while (running) {
        managerHub->inputManager->ResetIsPressed(); 

        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT) {
                running = false; 
                break; 
            }

            managerHub->inputManager->UpdateInputManager(event); 
        }

        managerHub->timeManager->UpdateTime(); 

        managerHub->entityManager->PushNewObjects(); 

        managerHub->renderer->UpdateRenderer(); 

        managerHub->entityManager->DeleteObjects(); 
    }
}