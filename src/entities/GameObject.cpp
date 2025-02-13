#include "GameObject.h"
#include "TextureManager.h"
#include <SDL_image.h>

#include <stdio.h>
#include <unistd.h>

#include <tuple>

using namespace std;

Collider::Collider(tuple<float, float> a, tuple<float, float> b, tuple<float, float> c, tuple<float, float> d) {
    this->a = a; 
    this->b = b; 
    this->c = c; 
    this->d = d; 
};

void Collider::OnCollision(Collision collison) {}


//void Collider::OnCollisionExit() {}

GameObject::GameObject(SDL_Renderer* renderer, string name, float posX, float posY, float posZ, float w, float h, float rotation, string texture_filepath, bool hasCollider) {
    this->name = name; 
    
    // Set transform parameters of this instance
    this->posX = posX;
    this->posY = posY;
    this->posZ = posZ; 
    this->w = w;
    this->h = h;
    this->rotation = rotation;

    // Set the rectangle for rendering
    this->rect.x = static_cast<int>(posX);
    this->rect.y = static_cast<int>(posY);
    this->rect.w = static_cast<int>(w);
    this->rect.h = static_cast<int>(h);

    this->texture_filepath = texture_filepath; 

    // Set the collider if the object is supposed to have one 
    this->hasCollider = hasCollider; 

    if (this->hasCollider) {
        this->collider.a = {posX, posY}; 
        this->collider.b = {posX, posY + h}; 
        this->collider.c = {posX + w, posY + h};
        this->collider.d = {posX + w, posY};   
    }

    // Set texture of this instance
    this->texture = TextureManager::GetInstance().LoadTexture(texture_filepath, renderer);
    if (!texture) {
        printf("GAMEOBJECT: Could not load associated texture! SDL_Error: %s\n", SDL_GetError());
    }
}

void GameObject::SetVelocity(float dx, float dy) {
    this->dx = dx; 
    this->dy = dy; 
}

// Function to move the gameobject. Can only be used from Update() in RUNTIME, since it uses deltaTime. 
void GameObject::UpdatePosition(float deltaTime) {
    this->rect.x += this->dx * deltaTime * 100; 
    this->rect.y += this->dy * deltaTime * 100; 
    this->posX = this->rect.x;
    this->posY = this->rect.y;
    this->collider.a = {this->posX, this->posY};
    this->collider.b = {this->posX, this->posY + this->h};
    this->collider.c = {this->posX + this->w, this->posY + this->h};
    this->collider.d = {this->posX + this->w, this->posY};
}

// Function to set the position of the gameobject.
void GameObject::SetPosition(float x, float y) {
    this->rect.x = static_cast<int>(x);
    this->rect.y = static_cast<int>(y);
    this->posX = x;
    this->posY = y;
    this->collider.a = {this->posX, this->posY};
    this->collider.b = {this->posX, this->posY + this->h};
    this->collider.c = {this->posX + this->w, this->posY + this->h};
    this->collider.d = {this->posX + this->w, this->posY};
}

/*
void GameObject::UpdateVelocity() {
    this->rect.x += this->dx; 
    this->rect.y += this->dy; 
}
*/

//posX, etc. are redundant since all the positional data is stored in rect anyway!

/* DEPRECATED -> Moved to constructor!
void GameObject::InitializeGameObject(SDL_Renderer* renderer, float posX, float posY, float posZ, 
                                       float scaleX, float scaleY, float rotation, const string& texture_filepath) {
    // Set transform parameters of this instance
    this->posX = posX;
    this->posY = posY;
    this->scaleX = scaleX;
    this->scaleY = scaleY;
    this->rotation = rotation;

    // Set the rectangle for rendering
    this->rect.x = static_cast<int>(posX);
    this->rect.y = static_cast<int>(posY);
    this->rect.w = static_cast<int>(scaleX);
    this->rect.h = static_cast<int>(scaleY);

    // Set texture of this instance
    this->texture = TextureManager::GetInstance().LoadTexture(texture_filepath, renderer);
    if (!texture) {
        printf("GAMEOBJECT: Could not load associated texture! SDL_Error: %s\n", SDL_GetError());
    }
}; 
*/