#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.h"
#include "CollisionManager.h"

#include <tuple>

using namespace std;

struct Collision; 

class Collider {
    public: 
    tuple<float, float> a; 
    tuple<float, float> b; 
    tuple<float, float> c; 
    tuple<float, float> d; 

    Collider(tuple<float, float> a = {1.0f, 1.0f}, tuple<float, float> b = {1.0f, 1.0f}, tuple<float, float> c = {1.0f, 1.0f}, tuple<float, float> d = {1.0f, 1.0f});   

    void OnCollision(Collision collison); 
    //void OnCollisionExit();   
}; 

enum ForceMode {
    // constant force 
    LINEAR, 
    // start weak and increase or start strong and decrease 
    QUADRATIC_EASE_IN, 
    QUADRATIC_EASE_OUT,
}; 

class Force {
    public: 
    float initialForce; 
    float currentForce = 0; 
    float last_frame_force; 

    float elapsed_time = 0; 
    float duration; 

    ForceMode updateMode; 

    Force(float inititalForce, float duration, ForceMode updateMode); 

    void UpdateForce(float deltaTime); 
}; 

class GameObject {
public:
    string name; 
    float posX, posY, posZ;
    float w, h;
    float rotation;

    //Filepath to image
    string texture_filepath; 

    //Velocity
    float dx, dy; 

    SDL_Texture* texture;
    SDL_Rect rect;

    //Collisions 
    Collider collider; 
    bool hasBody; 
    
    // dynamic forces
    vector<Force> forces; 

    // constant forces 
    // Gravity
    float gravity_force = 0;  

    // VELOCITY - Set and update velocity and corresponding forces:

    void SetVelocity(float dx = 1, float dy = 1);
    void UpdateVelocity(float deltaTime);
    void SetGravity(float gravity_force); 
    void ApplyForce(float initialForce, float duration, ForceMode updateMode); 


    // Set and Update position directly (.posX, .posY)

    void UpdatePosition(float deltaTime); 
    void SetPosition(float x, float y); 

    //Constructor
    GameObject(SDL_Renderer* renderer, string name, float posX = 0.0f, float posY = 0.0f, float posZ = 0.0f, 
                float scaleX = 100.0f, float scaleY = 100.0f, float rotation = 0.0f, 
                string texture_filepath = "/Users/jonathan/TelescopeEngine/media/sample_640×426.bmp", bool hasBody = true); 
};

#endif

/* DEPRECATED -> Moved to constructor!
void InitializeGameObject(SDL_Renderer* renderer, float posX = 0.0f, float posY = 0.0f, float posZ = 0.0f, 
                              float scaleX = 100.0f, float scaleY = 100.0f, float rotation = 0.0f, 
                              const string& texture_filepath = "/Users/jonathan/TelescopeEngine/media/sample_640×426.bmp");
*/