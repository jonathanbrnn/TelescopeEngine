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
                
                float overlapX = min(a->posX + a->w - b->posX, b->posX + b->w - a->posX);
                float overlapY = min(a->posY + a->h - b->posY, b->posY + b->h - a->posY); 
                
                if (overlapX < overlapY) {
                    if (a->dx != 0 && b->dx == 0) {  
                        // Only move 'a' if 'b' is static
                        if (a->posX < b->posX) {
                            a->SetPosition(a->posX - overlapX, a->posY);
                        } else {
                            a->SetPosition(a->posX + overlapX, a->posY);
                        }
                    } else if (b->dx != 0 && a->dx == 0) {  
                        // Only move 'b' if 'a' is static
                        if (b->posX < a->posX) {
                            b->SetPosition(b->posX - overlapX, b->posY);
                        } else {
                            b->SetPosition(b->posX + overlapX, b->posY);
                        }
                    } else {  
                        // Both moveable, split adjustment
                        if (a->posX < b->posX) {
                            a->SetPosition(a->posX - overlapX / 2, a->posY);
                            b->SetPosition(b->posX + overlapX / 2, b->posY);
                        } else {
                            a->SetPosition(a->posX + overlapX / 2, a->posY);
                            b->SetPosition(b->posX - overlapX / 2, b->posY);
                        }
                    }
                    a->dx = 0;
                    b->dx = 0;
                } else {
                    if (a->dy != 0 && b->dy == 0) {  
                        if (a->posY < b->posY) {
                            a->SetPosition(a->posX, a->posY - overlapY);
                        } else {
                            a->SetPosition(a->posX, a->posY + overlapY);
                        }
                    } else if (b->dy != 0 && a->dy == 0) {  
                        if (b->posY < a->posY) {
                            b->SetPosition(b->posX, b->posY - overlapY);
                        } else {
                            b->SetPosition(b->posX, b->posY + overlapY);
                        }
                    } else {  
                        if (a->posY < b->posY) {
                            a->SetPosition(a->posX, a->posY - overlapY / 2);
                            b->SetPosition(b->posX, b->posY + overlapY / 2);
                        } else {
                            a->SetPosition(a->posX, a->posY + overlapY / 2);
                            b->SetPosition(b->posX, b->posY - overlapY / 2);
                        }
                    }
                    a->dy = 0;
                    b->dy = 0;
                }    
                
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

                // Notify the objects of the collision
                a->collider.OnCollision(Collision(b->name, b->dx, b->dy, a->dx, a->dy, collision_point)); 
                b->collider.OnCollision(Collision(a->name, a->dx, a->dy, b->dx, b->dy, collision_point));
            }
        }        
    }
}

CollisionManager::CollisionManager(EntityManager &entityManager) : entityManager(entityManager) {}