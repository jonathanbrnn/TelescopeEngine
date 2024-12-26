#include "GameObject.h"
#include "TextureManager.h"
#include <SDL_image.h>

#include <stdio.h>
#include <unistd.h>

using namespace std;

void GameObject::InitializeGameObject(SDL_Renderer* renderer, float posX, float posY, float posZ, 
                                       float scaleX, float scaleY, float rotation, const string& img_filepath) {
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

    char cwd[1024]; 

    if (getcwd(cwd, sizeof(cwd)) != NULL){ printf("Current working dir: %s\n", cwd); } 


    // Set texture of this instance
    this->texture = TextureManager::GetInstance().LoadTexture(img_filepath, renderer);
    if (!texture) {
        printf("GAMEOBJECT: Could not load associated texture! SDL_Error: %s\n", SDL_GetError());
    }
};