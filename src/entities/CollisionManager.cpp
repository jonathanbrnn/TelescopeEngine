#include "core/ManagerHub.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include <tuple>
#include <vector>

using namespace std; 

void CollisionManager::ProcessCollisions() { 
    for(int i = 0; i < this->managerHub.entityManager->collision_objects.size(); i++) {
        for(int j = i + 1; j < this->managerHub.entityManager->collision_objects.size(); j++) {
            GameObject* a = this->managerHub.entityManager->collision_objects[i]; 
            GameObject* b = this->managerHub.entityManager->collision_objects[j]; 

            if (a->pos_x < b->pos_x + b->width && a->pos_x + a->width > b->pos_x &&
                 a->pos_y < b->pos_y + b->height && a->pos_y + a->height > b->pos_y) {
                
                float overlapX = min(a->pos_x + a->width - b->pos_x, b->pos_x + b->width - a->pos_x);
                float overlapY = min(a->pos_y + a->height - b->pos_y, b->pos_y + b->height - a->pos_y); 
                
                if (overlapX < overlapY) {
                    if (a->body->dx != 0 && b->body->dx == 0) {  
                        if (a->pos_x < b->pos_x) {
                            a->SetPosition(a->pos_x - overlapX, a->pos_y);
                        } else {
                            a->SetPosition(a->pos_x + overlapX, a->pos_y);
                        }
                    } else if (b->body->dx != 0 && a->body->dx == 0) {  
                        if (b->pos_x < a->pos_x) {
                            b->SetPosition(b->pos_x - overlapX, b->pos_y);
                        } else {
                            b->SetPosition(b->pos_x + overlapX, b->pos_y);
                        }
                    } else {  
                        if (a->pos_x < b->pos_x) {
                            a->SetPosition(a->pos_x - overlapX / 2, a->pos_y);
                            b->SetPosition(b->pos_x + overlapX / 2, b->pos_y);
                        } else {
                            a->SetPosition(a->pos_x + overlapX / 2, a->pos_y);
                            b->SetPosition(b->pos_x - overlapX / 2, b->pos_y);
                        }
                    }
                    a->body->dx = 0;
                    b->body->dx = 0;
                } else {
                    if (a->body->dy != 0 && b->body->dy == 0) {  
                        if (a->pos_y < b->pos_y) {
                            a->SetPosition(a->pos_x, a->pos_y - overlapY);
                        } else {
                            a->SetPosition(a->pos_x, a->pos_y + overlapY);
                        }
                    } else if (b->body->dy != 0 && a->body->dy == 0) {  
                        if (b->pos_y < a->pos_y) {
                            b->SetPosition(b->pos_x, b->pos_y - overlapY);
                        } else {
                            b->SetPosition(b->pos_x, b->pos_y + overlapY);
                        }
                    } else {  
                        if (a->pos_y < b->pos_y) {
                            a->SetPosition(a->pos_x, a->pos_y - overlapY / 2);
                            b->SetPosition(b->pos_x, b->pos_y + overlapY / 2);
                        } else {
                            a->SetPosition(a->pos_x, a->pos_y + overlapY / 2);
                            b->SetPosition(b->pos_x, b->pos_y - overlapY / 2);
                        }
                    }
                    a->body->dy = 0;
                    b->body->dy = 0;
                }    
                
                tuple<int, int> collision_point;

                if (a->pos_x < b->pos_x) {
                    collision_point = {a->pos_x + a->width, a->pos_y + a->height}; 
                }
                else if (a->pos_x > b->pos_x) {
                    collision_point = {a->pos_x, a->pos_y + a->height}; 
                }
                else if (a->pos_y < b->pos_y) {
                    collision_point = {a->pos_x + a->width, a->pos_y}; 
                }
                else if (a->pos_y > b->pos_y) {
                    collision_point = {a->pos_x, a->pos_y}; 
                }

                a->collider->OnCollision(Collision(b->name, b->body->dx, b->body->dy, a->body->dx, a->body->dy, collision_point)); 
                b->collider->OnCollision(Collision(a->name, a->body->dx, a->body->dy, b->body->dx, b->body->dy, collision_point));
            }
        }        
    }
}
