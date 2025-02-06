#include "../core/EntityManager.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include <tuple>
#include <vector>

using namespace std; 

Collision::Collision(string contact_name, float contact_dx, float contact_dy, float this_dx, float this_dy, tuple<int, int> collision_point) 
    : contact_id(contact_name), contact_dx(contact_dx), contact_dy(contact_dy),
      this_dx(this_dx), this_dy(this_dy), collision_point(collision_point) {}


void CollisionManager::ProcessCollisions() { 
    for(int i = 0; i < this->entityManager.collision_objects.size(); i++) {
        for(int j = i + 1; j < this->entityManager.collision_objects.size(); j++) {
            GameObject* a = this->entityManager.collision_objects[i]; 
            GameObject* b = this->entityManager.collision_objects[j]; 

            if (a->posX < b->posX + b->w && a->posX + a->w > b->posX &&
                 a->posY < b->posY + b->h && a->posY + a->h > b->posY) {
                
                tuple<int, int> collision_point;

                // Calculate the collision point
                if (a->posX < b->posX) {
                    collision_point = {a->posX + a->w, a->posY + a->h}; 
                }
                else if (a->posX > b->posX) {
                    collision_point = {a->posX, a->posY + a->h}; 
                }
                else if (a->posY < b->posY) {
                    collision_point = {a->posX + a->w, a->posY}; 
                }
                else if (a->posY > b->posY) {
                    collision_point = {a->posX, a->posY}; 
                }

                a->collider.OnCollision(Collision(b->name, b->dx, b->dy, a->dx, a->dy, collision_point)); 
                b->collider.OnCollision(Collision(a->name, a->dx, a->dy, b->dx, b->dy, collision_point));
            }
        }
        
    }
}

CollisionManager::CollisionManager(EntityManager &entityManager) : entityManager(entityManager) {}