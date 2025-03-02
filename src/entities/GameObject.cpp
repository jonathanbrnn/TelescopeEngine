#include <SDL_image.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

#include "GameObject.h"
#include "Force.h"
#include "Body.h"
#include "Collider.h"
#include "TextureManager.h"

using namespace std;

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