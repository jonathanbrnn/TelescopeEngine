#include "ManagerHub.h"

void ManagerHub::OnStart(EntityManager* entityManager, TimeManager* timeManager, CollisionManager* collisionManager, TextureManager* textureManager, InputManager* inputManager) {
    this->entityManager = entityManager; 
    this->timeManager = timeManager; 
    this->collisionManager = collisionManager;
    this->textureManager = textureManager;
    this->inputManager = inputManager;
}