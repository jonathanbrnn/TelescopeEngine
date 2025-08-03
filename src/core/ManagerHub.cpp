#include "ManagerHub.h"

void ManagerHub::OnStart(Camera* camera, EntityManager* entityManager, TimeManager* timeManager, CollisionManager* collisionManager, TextureManager* textureManager, InputManager* inputManager) {
    this->camera = camera;
    this->entityManager = entityManager;
    this->timeManager = timeManager;
    this->collisionManager = collisionManager;
    this->textureManager = textureManager;
    this->inputManager = inputManager;
}

void ManagerHub::SetStorage(int screen_width, int screen_height, SDL_Renderer* renderer) {
    this->screen_width = screen_width; 
    this->screen_height = screen_height; 
    this->renderer = renderer; 

    this->storage_set = true; 
}

int ManagerHub::Get_Screen_Width() {
    if (storage_set) { return screen_width; }
    else { 
        cout << "MANAGERHUB: WARNING! Returning -1 from Get_Screen_Width()." << endl; 
        return -1; 
    } 
}

int ManagerHub::Get_Screen_Height() {
    if (storage_set) { return screen_height; }
    else { 
        cout << "MANAGERHUB: WARNING! Returning -1 from Get_Screen_Height()." << endl; 
        return -1; 
    } 
}

SDL_Renderer* ManagerHub::Get_Renderer() {
    if (storage_set && renderer != nullptr) { return renderer; } 
    else {
        cout << "MANAGERHUB: WARNING! Returning nullptr from Get_Renderer()" << endl; 
        return nullptr; 
    }
}