#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>
#include "../entities/GameObject.h"
#include <tuple>
#include <map>

using namespace std; 

class GameObject;

class EntityManager {
    public: 
    explicit EntityManager(SDL_Renderer*& renderer); 

    static EntityManager& GetInstance(SDL_Renderer* renderer = nullptr); 
    
    void OnStart(vector<GameObject*>& gameObjects); 

    void Instantiate(string original_name, float posX = 0.0f, float posY = 0.0f, 
                    float posZ = 0.0f, float dx = 1.0f, float dy = 1.0f);

    void Delete(); 

    void OnEnd(); 

    void ProcessCollisions();

    GameObject* FindGameObjectByName(string name); 

    //all currently visible gm
    //passed to UpdateRenderer() 
    map<int, vector<GameObject*>> active_gameObjects; 

    // all objects that hold a collider
    vector<GameObject*> collision_objects; 

    private: 

    EntityManager(const EntityManager&) = delete; 
    EntityManager& operator=(const EntityManager&) = delete; 

    //Lookup table for gm by name 
    unordered_map<string, GameObject*> gameObjects;

    SDL_Renderer* renderer = renderer; 
};

#endif
 