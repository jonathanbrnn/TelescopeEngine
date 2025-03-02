#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "../core/ManagerHub.h"
#include "GameObject.h"
#include <tuple>
#include <vector>

using namespace std; 

class CollisionManager {
    public: 
    CollisionManager(const CollisionManager&) = delete;
    CollisionManager& operator=(const CollisionManager&) = delete; 

    static CollisionManager& GetInstance() {
        static CollisionManager instance; 
        return instance; 
    }
    
    void ProcessCollisions(); 

    private: 
    explicit CollisionManager();
    ManagerHub* managerHub;
};

#endif