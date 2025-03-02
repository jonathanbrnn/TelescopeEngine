#include "ManagerHub.h"
#include "EntityManager.h"
#include "TimeManager.h"
#include "../entities/CollisionManager.h"

void ManagerHub::OnStart(EntityManager* entityManager, TimeManager* timeManager, CollisionManager* collisionManager) {
    this->entityManager = entityManager; 
    this->timeManager = timeManager; 
    this->collisionManager = collisionManager;
}