#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>
#include "../entities/GameObject.h"
#include "../entities/Force.h"
#include "../entities/Body.h"
#include "../entities/Collider.h"
#include <tuple>
#include <map>

using namespace std; 

class GameObject;
struct Collider; 
class Body; 
enum ForceMode;
enum ForceAxis; 
class Force; 

class EntityManager {
    public: 
    explicit EntityManager(SDL_Renderer*& renderer); 

    // Returns the EntityManager. 
    // EntityManager is implemented using the singleton pattern.
    static EntityManager& GetInstance(SDL_Renderer* renderer = nullptr); 
    
    // Called before the first frame to collect all game objects.
    void OnStart(vector<GameObject*>& prefabs); 

    // Used to instantiate new objects based on prefabs during runtime. 
    void Instantiate(string prefab_name, float pos_x = NULL, float pos_y = NULL, 
                    float pos_z = NULL, float base_dx = NULL, float base_dy = NULL);

    void Delete(); 

    void OnEnd(); 

    GameObject* FindGameObjectByName(string name); 

    // All objects in the game. 
    vector<GameObject*> total_objects; 

    // All objects that are visible. 
    // Passed to the renderer. Sorted by their z-coordinate. 
    map<int, vector<GameObject*>> visible_objects; 

    // all objects that hold a collider
    vector<GameObject*> collision_objects; 

    // all objects that have a body
    vector<GameObject*> body_objects; 
 
    private: 

    EntityManager(const EntityManager&) = delete; 
    EntityManager& operator=(const EntityManager&) = delete; 

    SDL_Renderer* renderer = renderer; 
    
    //Lookup table for all game objects by name, only used for prefabs and lookup by name.  
    unordered_map<string, GameObject*> name_objects;
};

#endif
 