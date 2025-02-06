#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>
#include "../entities/GameObject.h"
#include <tuple>
#include <map>
#include "EntityManager.h"

EntityManager& EntityManager::GetInstance(SDL_Renderer* renderer) {
    static EntityManager instance(renderer); 
    return instance; 
}

//Pushes all hardcoded gameobjects created before runtime to gameObjects & active_gameObjects.
void EntityManager::OnStart(vector<GameObject*>& game_objects) {
     for (auto* gm: game_objects) { 
        cout << gm->posZ << gm->name << endl; 
        this->active_gameObjects[gm->posZ].push_back(gm);

        if (gm->hasCollider) {
            this->collision_objects.push_back(gm); 
        }

        if (this->gameObjects.find(gm->name) == this->gameObjects.end()) {
            this->gameObjects[gm->name] = gm; 
        }
        else {
            throw runtime_error("ENTITYMANAGER: Two separate game objects cannot share the same name. Choose a different name for '" + gm->name + "', or use Instantiate() to create a clone of the game object if they are the same.");
        }
     }
}

//Creates a clone of an existing game object. Can be used during runtime. 
void EntityManager::Instantiate(string original_name, float posX, float posY, float posZ, float dx, float dy) {
    GameObject* gm = new GameObject(renderer, original_name, posX, posY, posZ, 
                                this->gameObjects[original_name]->w, this->gameObjects[original_name]->h, 
                                this->gameObjects[original_name]->rotation, this->gameObjects[original_name]->texture_filepath, this->gameObjects[original_name]->hasCollider); 

    gm->SetVelocity(dx, dy); 
    this->active_gameObjects[gm->posZ].push_back(gm); 

    if (gm->hasCollider) {
        this->collision_objects.push_back(gm); 
    }
}

void EntityManager::Delete() {}

void EntityManager::OnEnd() {
    for (auto& [name, gm]: this->gameObjects) {
        delete gm; 
    }
    this->gameObjects.clear(); 

    for (auto& [posZ, gameObjects]: this->active_gameObjects) {
        for (int i = 0; i < gameObjects.size(); i++) {
            delete gameObjects[i]; 
        }
    }
    this->active_gameObjects.clear(); 

    for (int i = 0; i < this->collision_objects.size(); i++) {
        delete this->collision_objects[i]; 
    }
    this->collision_objects.clear(); 
}

void EntityManager::ProcessCollisions() {
    /*
    vector<GameObject*> toProcess; 

    for (auto i = active_gameObjects.begin(); i != active_gameObjects.end(); i++) {
        for (auto j = 0; j < i->second.size(); j++) {
            if (i->second[j]->hasCollider) {
                toProcess.push_back(i->second[j]); 
            }
        }
    } 
    */

   
}

GameObject* EntityManager::FindGameObjectByName(string name) {
    return this->gameObjects[name]; 
}

EntityManager::EntityManager (SDL_Renderer*& renderer) : renderer(renderer) {
    if (!renderer) {
        throw runtime_error("ENTITYMANAGER: Renderer cannot be null when initializing EntityManager!"); 
    }
}