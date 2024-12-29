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

class EntityManager {
    public: 
    explicit EntityManager(SDL_Renderer*& renderer); 

    static EntityManager& GetInstance(SDL_Renderer* renderer = nullptr); 
    
    void OnStart(vector<GameObject*> gameObjects); 

    void Instantiate(string original_name, float posX = 0.0f, float posY = 0.0f, 
                    float posZ = 0.0f, float dx = 1.0f, float dy = 1.0f);

    void Delete(); 

    //all currently visible gm
    //passed to UpdateRenderer() 
    map<int, vector<GameObject*>> active_gameObjects; 

    private: 

    EntityManager(const EntityManager&) = delete; 
    EntityManager& operator=(const EntityManager&) = delete; 

    //Lookup table for gm by name 
    unordered_map<string, GameObject*> gameObjects;

    SDL_Renderer* renderer = renderer; 
};

#endif