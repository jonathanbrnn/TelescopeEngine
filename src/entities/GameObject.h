#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <iostream>
#include <tuple>
#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.h"
#include "CollisionManager.h"

using namespace std;

struct Collision; 

// GAME OBJECT: 

class GameObject {
    public:
        // The game objects name. 
        // Must be unique. Used in the EntityManagers look up by name table and its Instantiate() method. 
        string name; 

        // POSITION: 
        // The objects position in 2D space. 
        float pos_x, pos_y;
        // The objects "depth". 
        // The higher the value, the further back the object is placed. 
        float pos_z;
        // The width and height of the object. 
        float width, height;
        // The objects rotation.
        // (!) Currently not implemented.
        float rotation;
    
        // Filepath to the image that should be used for the game objects texture, defines the appearance. 
        string texture_filepath; 
        // The objects texture.
        SDL_Texture* texture;
        // The area in which the texture is rendered. Defined by the pos_x, pos_y, width and height parameters. 
        SDL_Rect rect;

        // POSITION: 
        // Set pos_x, pos_y and pos_z (pos_z DEFAULT=NULL).
        void SetPosition(float pos_x, float pos_y, float pos_z = NULL);
        // Updates the game objects position every frame with its bodies velocity. Is only called if it has a body. 
        void UpdatePosition(float delta_time); 
    
        // COLLISION:   
        Collider* collider = nullptr; 

        // Adds a collider to the game object. 
        // Currently a game object only supports one collider at a time. 
        // (!) Currently colliders have the exact dimensions of the rect area. 
        void AddCollider();

        // BODY: 
        Body* body = nullptr;

        // Adds a body to the game object. 
        // A game object can only have one body. 
        void AddBody(float mass, bool use_gravity); 

        // CONSTRUCTOR: 
        // Set texture_filepath to "" to make it invisible.
        GameObject(SDL_Renderer* renderer, string name, float pos_x = 0, float pos_y = 0, float pos_z = 0, float width = 0, 
            float height = 0, float rotation = 0, string texture_filepath = "Users/Jonathan/TelescopeEngine/media/sample_640x426.bmp");
};  

// COLLIDER: 

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

// COLLISION: 

struct Collision {
    // "contact_attribute" -> the object the current game object is colliding with
    // "this_attribute" -> the current game object 

    public: 
    // CONTACT
    string contact_id; 

    float contact_dx; 
    float contact_dy; 

    // THIS 
    float this_dx; 
    float this_dy; 

    // An approximation of the point the two objects collide.
    tuple<int, int> collision_point;

    Collision(string contact_id, float contact_dx, float contact_dy, float this_dx, float this_dy, tuple<int, int> collision_point); 
}; 

// BODY: 

class Body {
    public: 
    // The mass of the body. Used to calculate the change in velocity of the body based on all current forces. 
    float mass = 1; 

    // The velocity of the body.
    // The velocity calculated every frame and applied to the game objects position: 
    float dx = 0; 
    float dy = 0; 
    // The base velocity of the body. Used to prevent accumulating force over time. 
    float base_dx = 0; 
    float base_dy = 0; 

    // Wether or not gravity (a constant downward force on the y-axis) is applied to the body. 
    bool use_gravity = true;
    float gravity_force = 1; 

    // Stores all active forces.
    vector<Force> forces; 

    // VELOCITY: 
    // Set's the dx, dy, base_dx and base_dy of the object.
    // dx DEFAULT=NULL 
    // dy DEFAULT=NULL 
    void SetVelocity(float dx = NULL, float dy = NULL); 
    // Updates the velocity by calculating all active forces and then adding them to the body's dx and dy.
    // (!) must be passed the current delta time. 
    void UpdateVelocity(float delta_time); 

    // FORCE'S: 
    // Add's a new force to the forces vector. Used to apply a new force to the body. 
    // update_mode determines the way the intensity of the force changes during it's lifetime (DEFAULT=LINEAR). 
    // axis determines the axis on which force is applied to (DEFAULT=AXIS_BOTH). 
    void ApplyForce(float initial_force, float duration, ForceMode update_mode = LINEAR, ForceAxis axis = AXIS_BOTH);  

    // CONSTRUCTOR: 
    // mass DEFAULT=1
    // use_gravity DEFAULT=true
    Body(float mass = 1, bool use_gravity = true); 
};

// FORCE: 

enum ForceMode {
    // constant force 
    LINEAR, 
    // start weak and increase or start strong and decrease 
    QUADRATIC_EASE_IN, 
    QUADRATIC_EASE_OUT,
}; 

enum ForceAxis {
    AXIS_X,
    AXIS_Y, 
    AXIS_BOTH
};

class Force {
    public: 
    float initial_force; 
    float current_force = 0; 
    float last_frame_force; 

    float elapsed_time = 0; 
    float duration; 

    ForceMode update_mode; 
    ForceAxis axis; 

    Force(float initial_force, float duration, ForceMode update_mode, ForceAxis axis = AXIS_BOTH); 

    void UpdateForce(float delta_time); 
}; 

#endif