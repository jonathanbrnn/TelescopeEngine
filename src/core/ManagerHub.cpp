#include "ManagerHub.h"
#include "EntityManager.h"

void ManagerHub::OnStart(ContextManager* contextManager, EntityManager* entityManager, TimeManager* timeManager, CollisionManager* collisionManager, TextureManager* textureManager, InputManager* inputManager) {
    this->contextManager = contextManager;
    this->entityManager = entityManager;
    this->timeManager = timeManager;
    this->collisionManager = collisionManager;
    this->textureManager = textureManager;
    this->inputManager = inputManager;
}
