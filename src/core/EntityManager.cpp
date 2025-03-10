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

void EntityManager::OnStart(vector<GameObject*>& prefabs) {
    for (auto* game_object: prefabs) {
        game_object->Start();
        total_objects.push_back(game_object);

        if (game_object->texture != nullptr) {
            visible_objects[game_object->pos_z].push_back(game_object);
        }

        
        if (game_object->collider != nullptr) {
            collision_objects.push_back(game_object);
        }

        if (game_object->body != nullptr) {
            body_objects.push_back(game_object);
        }

        if (name_objects.find(game_object->name) == name_objects.end()) {
            name_objects[game_object->name] = game_object;
        }
        else {
            cout << "ENTITYMANAGER: Two separate game objects cannot share the same name. Choose a different name for '" + game_object->name + "', or use Instantiate() to create a clone of the game object if they are the same." << endl;
        }
    }
}

void EntityManager::Instantiate(string prefab_name, float pos_x, float pos_y, float pos_z, float base_dx, float base_dy) {
    if (name_objects.find(prefab_name) == name_objects.end()) {
        cout << "ENTITYMANAGER: No prefab with the name: " << prefab_name << " could be found!" << endl;
        return;
    }

    GameObject* clone = new GameObject(renderer, prefab_name, pos_x, pos_y, pos_z, name_objects[prefab_name]->width, name_objects[prefab_name]->height, name_objects[prefab_name]->rotation, name_objects[prefab_name]->texture_filepath);
    
    clone->Start();

    // Handle colliders and body
    if (clone->collider != nullptr) clone->AddCollider();
    if (clone->body != nullptr) {
        if (base_dx == NULL) { base_dx = clone->body->base_dx; }
        if (base_dy == NULL) { base_dy = clone->body->base_dy; }
        clone->body->SetVelocity(base_dx, base_dy);
    }

    // Store it
    EntityManager::GetInstance().total_objects.push_back(clone);
    if (!clone->texture_filepath.empty()) {
        EntityManager::GetInstance().visible_objects[pos_z].push_back(clone);
    }
    if (clone->collider) {
        EntityManager::GetInstance().collision_objects.push_back(clone);
    }
    if (clone->body) {
        EntityManager::GetInstance().body_objects.push_back(clone);
    }
}

void EntityManager::AddNewObject(GameObject* game_object) {
    temporal_objects.push_back(game_object); 
}

void EntityManager::PushNewObjects() {
    if (temporal_objects.size() == 0) { return; }

    for (auto game_object : temporal_objects) {
        game_object->Start();
        total_objects.push_back(game_object); 

        if (game_object->texture != nullptr) {
            visible_objects[game_object->pos_z].push_back(game_object); 
        }

        if (game_object->collider != nullptr) {
            collision_objects.push_back(game_object);
        }

        if (game_object->body != nullptr) {
            body_objects.push_back(game_object); 
        }

        if(name_objects.find(game_object->name) == name_objects.end()) {
            name_objects[game_object->name] = game_object; 
        }
    }

    temporal_objects.clear();
}

void EntityManager::Delete() {}

void EntityManager::OnEnd() {
    for (auto& game_object : total_objects) { delete game_object; }
    total_objects.clear();

    for (auto& [pos_z, game_object_vector] : visible_objects) { 
        for (auto& game_object : game_object_vector) {
            delete game_object;
        }
        game_object_vector.clear();
    }
    visible_objects.clear();

    for (auto& game_object : collision_objects) { delete game_object; }
    collision_objects.clear();

    for (auto& game_object : body_objects) { delete game_object; }
    body_objects.clear();

    for (auto& [name, game_object] : name_objects) { delete game_object; }
    name_objects.clear();
}

GameObject* EntityManager::FindGameObjectByName(string name) {
    if (name_objects.find(name) != name_objects.end()) {
        return name_objects[name]; 
    }
    else {
        cout << "ENTITYMANAGER: Warning game object with the name: '" << name << "' could not be found!" << endl;
    }
}

EntityManager::EntityManager (SDL_Renderer*& renderer) : renderer(renderer) {
    if (!renderer) {
        throw runtime_error("ENTITYMANAGER: Renderer cannot be null when initializing EntityManager!"); 
    }
}