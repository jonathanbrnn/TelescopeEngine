#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <vector>
#include "../core/EntityManager.h"

using namespace std; 

class GameObject;
class EntityManager; 

struct Collision {
    /*
    "contact_attribute" -> the object the current game object is colliding with
    "this_attribute" -> the current game object 
    */ 


    public: 
    // CONTACT
    string contact_id; 

    float contact_dx; 
    float contact_dy; 

    // THIS 
    float this_dx; 
    float this_dy; 

    // An approximation of the point the two objects collide
    tuple<int, int> collision_point;

    Collision(string contact_id, float contact_dx, float contact_dy, float this_dx, float this_dy, tuple<int, int> collision_point); 
}; 

class CollisionManager {
    public: 
    CollisionManager(EntityManager &entityManager);  
    
    void ProcessCollisions(); 

    private: 
    EntityManager &entityManager; 
};

#endif 