#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>
#include "../entities/GameObject.h"
#include <tuple>
#include "EntityManager.h"

EntityManager& EntityManager::GetInstance(SDL_Renderer* renderer) {
    static EntityManager instance(renderer); 
    return instance; 
}

void EntityManager::OnStart(vector<GameObject*> game_objects) {
     for (auto* gm: game_objects) { 
        this->active_gameObjects[gm->posZ].push_back(gm);
        this->gameObjects[gm->name] = gm; 
     }
}

void EntityManager::Instantiate(string original_name, float posX, float posY, float posZ, float dx, float dy) {
    GameObject* gm = new GameObject(renderer, original_name, posX, posY, posZ, 
                                this->gameObjects[original_name]->scaleX, this->gameObjects[original_name]->scaleY, 
                                this->gameObjects[original_name]->rotation, this->gameObjects[original_name]->texture_filepath); 

    gm->SetVelocity(dx, dy); 
    this->active_gameObjects[gm->posZ].push_back(gm); 
}

EntityManager::EntityManager (SDL_Renderer*& renderer) : renderer(renderer) {
    if (!renderer) {
        throw runtime_error("Renderer cannot be null when initializing EntityManager!"); 
    }
}