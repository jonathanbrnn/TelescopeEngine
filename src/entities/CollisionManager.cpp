#include "../core/ManagerHub.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include <tuple>
#include <vector>

using namespace std;

CollisionManager::CollisionManager() : managerHub(nullptr) {}

void CollisionManager::OnStart(ManagerHub* managerHub) {
    this->managerHub = managerHub;
}

void CollisionManager::ProcessCollisions() {
    for (int i = 0; i < this->managerHub->entityManager->collision_objects.size(); i++) {
        for (int j = i + 1; j < this->managerHub->entityManager->collision_objects.size(); j++) {
            GameObject* a = this->managerHub->entityManager->collision_objects[i];
            GameObject* b = this->managerHub->entityManager->collision_objects[j];

            float a_current_width = a->width * a->scale_x;
            float a_current_height = a->height * a->scale_y;

            float b_current_width = b->width * b->scale_x;
            float b_current_height = b->height * b->scale_y;

            if (a->pos_x < b->pos_x + b_current_width && a->pos_x + a_current_width > b->pos_x &&
                a->pos_y < b->pos_y + b_current_height && a->pos_y + a_current_height > b->pos_y) {

                float overlapX = min(a->pos_x + a_current_width - b->pos_x, b->pos_x + b_current_width - a->pos_x);
                float overlapY = min(a->pos_y + a_current_height - b->pos_y, b->pos_y + b_current_height - a->pos_y);

                CollisionSide a_collision_side;
                CollisionSide b_collision_side;

                if (overlapX < overlapY) {
                    if (a->body != nullptr && a->body->dx != 0 && (b->body == nullptr || b->body->dx == 0)) {
                        if (a->pos_x < b->pos_x) {
                            a->SetPosition(a->pos_x - overlapX, a->pos_y);
                            a_collision_side = RIGHT;
                            b_collision_side = LEFT;
                        } else {
                            a->SetPosition(a->pos_x + overlapX, a->pos_y);
                            a_collision_side = LEFT;
                            b_collision_side = RIGHT;
                        }
                    } else if (b->body != nullptr && b->body->dx != 0 && (a->body == nullptr || a->body->dx == 0)) {
                        if (b->pos_x < a->pos_x) {
                            b->SetPosition(b->pos_x - overlapX, b->pos_y);
                            a_collision_side = LEFT;
                            b_collision_side = RIGHT;
                        } else {
                            b->SetPosition(b->pos_x + overlapX, b->pos_y);
                            a_collision_side = RIGHT;
                            b_collision_side = LEFT;
                        }
                    } else {
                        if (a->pos_x < b->pos_x) {
                            a->SetPosition(a->pos_x - overlapX / 2, a->pos_y);
                            b->SetPosition(b->pos_x + overlapX / 2, b->pos_y);
                            a_collision_side = RIGHT;
                            b_collision_side = LEFT;
                        } else {
                            a->SetPosition(a->pos_x + overlapX / 2, a->pos_y);
                            b->SetPosition(b->pos_x - overlapX / 2, b->pos_y);
                            a_collision_side = LEFT;
                            b_collision_side = RIGHT;
                        }
                    }
                    if (a->body != nullptr) a->body->dx = 0;
                    if (b->body != nullptr) b->body->dx = 0;
                } else {
                    if (a->body != nullptr && a->body->dy != 0 && (b->body == nullptr || b->body->dy == 0)) {
                        if (a->pos_y < b->pos_y) {
                            a->SetPosition(a->pos_x, a->pos_y - overlapY);
                            a_collision_side = BOTTOM;
                            b_collision_side = TOP;
                        } else {
                            a->SetPosition(a->pos_x, a->pos_y + overlapY);
                            a_collision_side = TOP;
                            b_collision_side = BOTTOM;
                        }
                    } else if (b->body != nullptr && b->body->dy != 0 && (a->body == nullptr || a->body->dy == 0)) {
                        if (b->pos_y < a->pos_y) {
                            b->SetPosition(b->pos_x, b->pos_y - overlapY);
                            a_collision_side = TOP;
                            b_collision_side = BOTTOM;
                        } else {
                            b->SetPosition(b->pos_x, b->pos_y + overlapY);
                            a_collision_side = BOTTOM;
                            b_collision_side = TOP;
                        }
                    } else {
                        if (a->pos_y < b->pos_y) {
                            a->SetPosition(a->pos_x, a->pos_y - overlapY / 2);
                            b->SetPosition(b->pos_x, b->pos_y + overlapY / 2);
                            a_collision_side = BOTTOM;
                            b_collision_side = TOP;
                        } else {
                            a->SetPosition(a->pos_x, a->pos_y + overlapY / 2);
                            b->SetPosition(b->pos_x, b->pos_y - overlapY / 2);
                            a_collision_side = TOP;
                            b_collision_side = BOTTOM;
                        }
                    }
                    if (a->body != nullptr) a->body->dy = 0;
                    if (b->body != nullptr) b->body->dy = 0;
                }

                tuple<int, int> collision_point;

                if (a->pos_x < b->pos_x) {
                    collision_point = {a->pos_x + a_current_width, a->pos_y + a_current_height};
                } else if (a->pos_x > b->pos_x) {
                    collision_point = {a->pos_x, a->pos_y + a_current_height};
                } else if (a->pos_y < b->pos_y) {
                    collision_point = {a->pos_x + a_current_width, a->pos_y};
                } else if (a->pos_y > b->pos_y) {
                    collision_point = {a->pos_x, a->pos_y};
                }

                a->OnCollision(Collision(b->name, b->body != nullptr ? b->body->dx : 0, b->body != nullptr ? b->body->dy : 0, a->body != nullptr ? a->body->dx : 0, a->body != nullptr ? a->body->dy : 0, a_collision_side, collision_point));
                b->OnCollision(Collision(a->name, a->body != nullptr ? a->body->dx : 0, a->body != nullptr ? a->body->dy : 0, b->body != nullptr ? b->body->dx : 0, b->body != nullptr ? b->body->dy : 0, b_collision_side, collision_point));
            }
        }
    }
}
