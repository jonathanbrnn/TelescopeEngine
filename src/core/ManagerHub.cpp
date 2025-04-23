#include "ManagerHub.h"

void ManagerHub::OnStart(Camera* camera, EntityManager* entityManager, TimeManager* timeManager, CollisionManager* collisionManager, TextureManager* textureManager, InputManager* inputManager) {
    this->camera = camera;
    this->entityManager = entityManager;
    this->timeManager = timeManager;
    this->collisionManager = collisionManager;
    this->textureManager = textureManager;
    this->inputManager = inputManager;
}
