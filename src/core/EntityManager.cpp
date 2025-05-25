#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
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
        game_object->CheckGameObject();
        total_objects.push_back(game_object);

        if (game_object->texture != nullptr || game_object->texture_filepath != "") {
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

    //GameObject* clone = new GameObject(renderer, prefab_name, pos_x, pos_y, pos_z, name_objects[prefab_name]->width, name_objects[prefab_name]->height, name_objects[prefab_name]->rotation, name_objects[prefab_name]->texture_filepath);
    GameObject* clone = name_objects[prefab_name]->Clone();


    if (clone_version.find(prefab_name) == clone_version.end()) {
        clone_version[prefab_name] = 0;
    }
    else {
        clone_version[prefab_name] = clone_version[prefab_name] + 1;
    }

    clone->name = clone->name + "_" + to_string(clone_version[prefab_name]);

    if (pos_x && pos_y) {
        clone->SetPosition(pos_x, pos_y);
    }
    else if (pos_z) {
        clone->SetPosition(pos_x, pos_y, pos_z);
    }
    else {
        cout << "ENTITYMANAGER: Could not set the position of: " << clone->name << " because the values were not provided." << endl;
        cout << "The position has been set to the prefabs." << endl;
    }

    clone->Start();

    // THIS MAKES NO SENSE AT ALL WHAT THE FUCK -> FIX IT!! if base_dx is the same as saying if base_dx != 0.
    if (clone->body != nullptr) {
        if ((base_dx && base_dy)) {
            clone->body->SetVelocityBothAxis(base_dx, base_dy);
        }
        else if (base_dx) {
            clone->body->SetDX(base_dx);
        }
        else if (base_dy) {
            clone->body->SetDY(base_dy);
        }
        else if ((base_dx || base_dy) && clone->body == nullptr) {
            cout << "ENTITYMANAGER: Could not apply velocity to: " << clone->name << " since the prefab has no body attached to it." << endl;
        }
    }


    // Store it
    AddNewObject(clone);

    /*
    An earlier "solution" kept crashing because it was adding the objects directly to the relevant vectors within this method.
    This caused a curious bug where the first eight objects added using Instantiate() worked perfectly fine, the ninth however, caused the game to crash.
    This is due to the buffer of each vector holding up to eight objects before allocating new memory.
    Since Instantiate() was called from an Update() method, the vector (total_objects) was trying to reallocate new memory while being iterated over.
    */
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
        else {
            cout << "ENTITYMANAGER: A game object with name: " << game_object->name << " already exist. Finding this object won't be possible using FindGameObjectByName()." << endl;
        }
    }

    temporal_objects.clear();
}

void EntityManager::Delete(string name) {
    temporal_to_delete.push_back(name);
}

void EntityManager::DeleteObjects() {
    for (auto name : temporal_to_delete) {
        GameObject* to_delete = FindGameObjectByName(name);

        if (to_delete) {
            for (auto it = total_objects.begin(); it != total_objects.end(); ++it) {
                if ((*it)->name == name) {
                    total_objects.erase(it);
                    break;
                }
            }

            name_objects.erase(name);

            auto& visible_list = visible_objects[to_delete->pos_z];
            for (auto it = visible_list.begin(); it != visible_list.end(); ++it) {
                if ((*it)->name == name) {
                    visible_list.erase(it);
                    break;
                }
            }

            if (to_delete->collider) {
                for (auto it = collision_objects.begin(); it != collision_objects.end(); ++it) {
                    if ((*it)->name == name) {
                        collision_objects.erase(it);
                        break;
                    }
                }
            }

            if (to_delete->body) {
                for (auto it = body_objects.begin(); it != body_objects.end(); ++it) {
                    if ((*it)->name == name) {
                        body_objects.erase(it);
                        break;
                    }
                }
            }

            //delete to_delete;
        }
        else {
            cout << "ENTITYMANAGER: Warning! Object with name: " << name << " could not be deleted because it wasn't found. Did you enter the name in correctly?" << endl;
        }
    }

    temporal_to_delete.clear();
}

void EntityManager::OnEnd() {
    for (auto& game_object : total_objects) { cout << game_object->name << endl; delete game_object; }
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
