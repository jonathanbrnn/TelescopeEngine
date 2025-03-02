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
        cout << "ENTITYMANAGER: Prefab with name: " << prefab_name << " was not found!" << endl;
        return; 
    }

    bool has_collider = name_objects[prefab_name]->collider != nullptr;

    bool has_body = name_objects[prefab_name]->body != nullptr; 

    if (pos_x == NULL) { pos_x = name_objects[prefab_name]->pos_x; }
    if (pos_y == NULL) { pos_y = name_objects[prefab_name]->pos_y; }
    if (pos_z == NULL) { pos_z = name_objects[prefab_name]->pos_z; }

    GameObject* clone = new GameObject(renderer, prefab_name, pos_x, pos_y, pos_z, name_objects[prefab_name]->width, name_objects[prefab_name]->height, 
                                    name_objects[prefab_name]->rotation, name_objects[prefab_name]->texture_filepath);
    
    if (has_collider) {
        clone->AddCollider();
    }

    if (has_body) {
        if (base_dx == NULL) { base_dx == name_objects[prefab_name]->body->base_dx; }
        if (base_dy == NULL) { base_dy == name_objects[prefab_name]->body->base_dy; }
    }
                        
    if (has_body) {
        clone->AddBody(name_objects[prefab_name]->body->mass, name_objects[prefab_name]->body->use_gravity);
    }

    total_objects.push_back(clone);

    if (clone->texture_filepath != "") {
        visible_objects[pos_z].push_back(clone);
    }

    if (has_collider) {
        collision_objects.push_back(clone);
    }

    if (has_body) {
        body_objects.push_back(clone);
    }
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