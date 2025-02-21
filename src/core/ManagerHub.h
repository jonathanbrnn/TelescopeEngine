#ifndef MANAGERHUB_H
#define MANAGERHUB_H

#include "EntityManager.h"
#include "TimeManager.h"
#include "../entities/CollisionManager.h"

class ManagerHub {
public:
    // Deleted copy constructor and assignment operator to prevent duplicates
    ManagerHub(const ManagerHub&) = delete;
    ManagerHub& operator=(const ManagerHub&) = delete;

    // Static method to get the single instance
    static ManagerHub& GetInstance(EntityManager* entityManager = nullptr, 
                                   TimeManager* timeManager = nullptr, 
                                   CollisionManager* collisionManager = nullptr) {
        static ManagerHub instance(entityManager, timeManager, collisionManager);
        return instance;
    }

    EntityManager* entityManager = nullptr; 
    TimeManager* timeManager = nullptr; 
    CollisionManager* collisionManager = nullptr; 

private:
    // Private constructor ensures no external instantiation
    explicit ManagerHub(EntityManager* entityManager, 
                        TimeManager* timeManager, 
                        CollisionManager* collisionManager) 
        : entityManager(entityManager), 
          timeManager(timeManager), 
          collisionManager(collisionManager) {}
};

#endif
