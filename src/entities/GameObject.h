#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.h"

using namespace std;

class GameObject {
public:
/* DEPRECATED -> Moved to constructor!
void InitializeGameObject(SDL_Renderer* renderer, float posX = 0.0f, float posY = 0.0f, float posZ = 0.0f, 
                              float scaleX = 100.0f, float scaleY = 100.0f, float rotation = 0.0f, 
                              const string& texture_filepath = "/Users/jonathan/TelescopeEngine/media/sample_640×426.bmp");
*/
    string name; 
    float posX, posY, posZ;
    float scaleX, scaleY;
    float rotation;

    //Filepath to image
    string texture_filepath; 

    //Velocity
    float dx, dy; 

    SDL_Texture* texture;
    SDL_Rect rect;

    void SetVelocity(float dx = 1, float dy = 1);

    void UpdateVelocity(); 
   
    GameObject(SDL_Renderer* renderer, string name, float posX = 0.0f, float posY = 0.0f, float posZ = 0.0f, 
                float scaleX = 100.0f, float scaleY = 100.0f, float rotation = 0.0f, 
                string texture_filepath = "/Users/jonathan/TelescopeEngine/media/sample_640×426.bmp"); 
};

#endif
