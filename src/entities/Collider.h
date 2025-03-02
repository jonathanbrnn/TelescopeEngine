#ifndef COLLIDER_H
#define COLLIDER_H

#include <iostream>

using namespace std; 

// COLLISION: 

struct Collision {
    // "contact_attribute" -> the object the current game object is colliding with
    // "this_attribute" -> the current game object 

    public: 
    // CONTACT
    string contact_name; 

    float contact_dx; 
    float contact_dy; 

    // THIS 
    float this_dx; 
    float this_dy; 

    // An approximation of the point the two objects collide.
    tuple<int, int> collision_point;

    Collision(string contact_id, float contact_dx, float contact_dy, float this_dx, float this_dy, tuple<int, int> collision_point); 
}; 

// COLLIDER: 

struct Collider {
    public: 
    tuple<float, float> a; 
    tuple<float, float> b; 
    tuple<float, float> c; 
    tuple<float, float> d;  

    Collider(tuple<float, float> a = {1.0f, 1.0f}, tuple<float, float> b = {1.0f, 1.0f}, tuple<float, float> c = {1.0f, 1.0f}, tuple<float, float> d = {1.0f, 1.0f});   

    void OnCollision(Collision collison); 
    //void OnCollisionExit();   
}; 

#endif