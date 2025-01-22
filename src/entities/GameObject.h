#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.h"

#include <tuple>

using namespace std;

struct Collider {
    tuple<float, float> a; 
    tuple<float, float> b; 
    tuple<float, float> c; 
    tuple<float, float> d; 

    Collider(tuple<float, float> a = {1.0f, 1.0f}, tuple<float, float> b = {1.0f, 1.0f}, tuple<float, float> c = {1.0f, 1.0f}, tuple<float, float> d = {1.0f, 1.0f});     
}; 

class GameObject {
public:
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

    //Collisions 
    Collider collider; 
    bool hasCollider; 


    void SetVelocity(float dx = 1, float dy = 1);

    /*
    void UpdateVelocity();
    */

   void UpdatePosition(float deltaTime); 

   
    GameObject(SDL_Renderer* renderer, string name, float posX = 0.0f, float posY = 0.0f, float posZ = 0.0f, 
                float scaleX = 100.0f, float scaleY = 100.0f, float rotation = 0.0f, 
                string texture_filepath = "/Users/jonathan/TelescopeEngine/media/sample_640×426.bmp", bool hasCollider = true); 
};

#endif

/* DEPRECATED -> Moved to constructor!
void InitializeGameObject(SDL_Renderer* renderer, float posX = 0.0f, float posY = 0.0f, float posZ = 0.0f, 
                              float scaleX = 100.0f, float scaleY = 100.0f, float rotation = 0.0f, 
                              const string& texture_filepath = "/Users/jonathan/TelescopeEngine/media/sample_640×426.bmp");
*/