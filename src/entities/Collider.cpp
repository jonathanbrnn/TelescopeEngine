#include "Collider.h"

// COLLISION: 

Collision::Collision(string contact_name, float contact_dx, float contact_dy, float this_dx, float this_dy, tuple<int, int> collision_point) {
    this->contact_name = contact_name; 
    this->contact_dx = contact_dx; 
    this->contact_dy = contact_dy; 
    this->this_dx = this_dx; 
    this->this_dy = this_dy;
    this->collision_point = collision_point;
}

// COLLIDER: 

Collider::Collider(tuple<float, float> a, tuple<float, float> b, tuple<float, float> c, tuple<float, float> d) {
    this->a = a; 
    this->b = b; 
    this->c = c; 
    this->d = d; 
}

void Collider::OnCollision(Collision collision) {}

