#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <vector>
#include "../core/ManagerHub.h"

using namespace std; 

class GameObject;
class EntityManager; 

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
    explicit CollisionManager() {}
    ManagerHub& managerHub = ManagerHub::GetInstance(); 
};

#endif 