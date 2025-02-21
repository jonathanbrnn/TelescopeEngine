#include "GameObject.h"
#include "TextureManager.h"
#include <SDL_image.h>

#include <stdio.h>
#include <unistd.h>

#include <tuple>

using namespace std;

// GAME OBJECT: 

GameObject::GameObject(SDL_Renderer* renderer, string name, float pos_x, float pos_y, float pos_z, float width, float height, float rotation, string texture_filepath) {
    this->name = name; 
    
    this->pos_x = pos_x; 
    this->pos_y = pos_y; 
    this->pos_z = pos_z;

    this->width = width; 
    this->height = height; 
    
    this->rotation = rotation;
    
    // Set SDL_Rect's parameters
    rect.x = static_cast<int>(pos_x);
    rect.y = static_cast<int>(pos_y);
    rect.w = static_cast<int>(width);
    rect.h = static_cast<int>(height);
    
    if (texture_filepath != "") {
        // Set texture of this instance
        texture = TextureManager::GetInstance().LoadTexture(texture_filepath, renderer);
        if (!texture) {
            printf("GAMEOBJECT: Could not load associated texture! SDL_Error: %s\n", SDL_GetError());
        }
    }
    else {
        texture = nullptr; 
    }
}

void GameObject::SetPosition(float pos_x, float pos_y, float pos_z) {
    rect.x = static_cast<int>(pos_x);
    rect.y = static_cast<int>(pos_y);
    
    this->pos_x = pos_x; 
    this->pos_y = pos_y; 
    if (pos_z != NULL) {
        this->pos_z = pos_z;
    }

    if (collider != nullptr) {
        collider->a = {pos_x, pos_x};
        collider->b = {pos_x, pos_y + height};
        collider->c = {pos_x + width, pos_y + height};
        collider->d = {pos_x + width, pos_y};
    }
}

void GameObject::UpdatePosition(float delta_time) {
    if (body != nullptr) {
        rect.x += body->dx * delta_time * 100; 
        rect.y += body->dy * delta_time * 100; 

        pos_x = rect.x; 
        pos_y = rect.y; 

        if (collider != nullptr) {
            collider->a = {pos_x, pos_y};
            collider->b = {pos_x, pos_y + height};
            collider->c = {pos_x + width, pos_y + height};
            collider->d = {pos_x + width, pos_y};
        }
    }
}

void GameObject::AddCollider() {
    if (collider == nullptr) {
        collider = new Collider({pos_x, pos_y}, {pos_x, pos_x + height}, {pos_x + width, pos_y + height}, {pos_x + width, pos_y}); 
    }
    else {
        cout << "GAMEOBJECT: The object " << name << " already has a collider attached to it!" << endl; 
    }
}

void GameObject::AddBody(float mass, bool use_gravity) {
    if (body != nullptr) {
        body = new Body(mass, use_gravity);
    }
    else {
        cout << "GAMEOBJECT: The object " << name << "already has a body attached to it!" << endl;
    }
}

// COLLIDER: 

Collider::Collider(tuple<float, float> a, tuple<float, float> b, tuple<float, float> c, tuple<float, float> d) {
    this->a = a; 
    this->b = b; 
    this->c = c; 
    this->d = d; 
}

void Collider::OnCollision(Collision collision) {}

// COLLISION: 

Collision::Collision(string contact_name, float contact_dx, float contact_dy, float this_dx, float this_dy, tuple<int, int> collision_point) 
    : contact_id(contact_name), contact_dx(contact_dx), contact_dy(contact_dy),
      this_dx(this_dx), this_dy(this_dy), collision_point(collision_point) {}

// BODY: 

Body::Body(float mass, bool use_gravity) {
    this->mass = mass; 
    this->use_gravity = use_gravity;
    
    if (this->use_gravity) {
        // gravity_force = mass * storage.gravity_constant; 
    }
}

void Body::SetVelocity(float dx, float dy) {
    if (dx != NULL) {
        base_dx = dx; 
        this->dx = dy; 
    }
    if (dy != NULL) {
        base_dy = dy; 
        this->dy = dy; 
    }
}

void Body::UpdateVelocity(float delta_time) {
    dx = base_dx; 
    dy = base_dy; 

    for (auto force : forces) {
        force.UpdateForce(delta_time);

        if (force.axis == AXIS_X || force.axis == AXIS_BOTH) {
            dx += force.current_force; 
        }
        if (force.axis == AXIS_Y || force.axis == AXIS_BOTH) {
            dy += force.current_force; 
        }
    }

    if (use_gravity) {
        dy += gravity_force;
    }
}

void Body::ApplyForce(float initial_force, float duration, ForceMode update_mode, ForceAxis axis) {
    forces.emplace_back(initial_force, duration, update_mode, axis); 
}

// FORCE: 

Force::Force(float initial_force, float duration, ForceMode update_mode, ForceAxis axis) {
    this->initial_force = initial_force; 
    
    this->duration = duration; 

    this->update_mode = update_mode; 
    this->axis = axis; 
}