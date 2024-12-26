#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.h"

using namespace std;

class GameObject {
public:
    void InitializeGameObject(SDL_Renderer* renderer, float posX = 0.0f, float posY = 0.0f, float posZ = 0.0f, 
                              float scaleX = 100.0f, float scaleY = 100.0f, float rotation = 0.0f, 
                              const string& img_filepath = "../media/sample_640x426.bmp");

    float posX, posY, posZ;
    float scaleX, scaleY;
    float rotation;

    SDL_Texture* texture;
    SDL_Rect rect;
};

#endif
