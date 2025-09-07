#include "ManagerHub.h"

void ManagerHub::OnStart(Renderer* renderer, Camera* camera, EntityManager* entityManager, TimeManager* timeManager, SceneManager* sceneManager, CollisionManager* collisionManager, TextureManager* textureManager, InputManager* inputManager) {
    this->renderer = renderer; 
    this->camera = camera;
    this->entityManager = entityManager;
    this->timeManager = timeManager;
    this->sceneManager = sceneManager; 
    this->collisionManager = collisionManager;
    this->textureManager = textureManager;
    this->inputManager = inputManager;
}

void ManagerHub::SetStorage(int screen_width, int screen_height) {
    this->screen_width = screen_width; 
    this->screen_height = screen_height; 

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

ManagerHub::~ManagerHub() { 
}