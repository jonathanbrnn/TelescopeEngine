#include "GameObject.h"
#include "TextureManager.h"
#include <SDL_image.h>

#include <stdio.h>
#include <unistd.h>

using namespace std;

GameObject::GameObject(SDL_Renderer* renderer, string name, float posX, float posY, float posZ, float scaleX, float scaleY, float rotation, string texture_filepath) {
    this->name = name; 
    
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

    this->texture_filepath = texture_filepath; 

    // Set texture of this instance
    this->texture = TextureManager::GetInstance().LoadTexture(texture_filepath, renderer);
    if (!texture) {
        printf("GAMEOBJECT: Could not load associated texture! SDL_Error: %s\n", SDL_GetError());
    }
}

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

void GameObject::SetVelocity(float dx, float dy) {
    this->dx = dx; 
    this->dy = dy; 
}

void GameObject::UpdateVelocity() {
    this->rect.x += this->dx; 
    this->rect.y += this->dy; 
}

//posX, etc. are redundant since all the positional data is stored in rect anyway!