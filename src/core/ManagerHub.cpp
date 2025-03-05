#include "ManagerHub.h"

void ManagerHub::OnStart(EntityManager* entityManager, TimeManager* timeManager, CollisionManager* collisionManager, InputManager* inputManager) {
    this->entityManager = entityManager; 
    this->timeManager = timeManager; 
    this->collisionManager = collisionManager;
    this->inputManager = inputManager;
}