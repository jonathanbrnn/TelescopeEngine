#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <iostream>
#include <functional>
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

    // Used to add a new game object during runtime.
    void AddNewObject(GameObject* game_object);

    // Called before all game objects are updated each frame.
    // Pushes all game objects stored in the temporal_objects vector to the respective relevant vector.
    void PushNewObjects();

    // Deletes a game object by name.
    void Delete(string name);

    // Deletes all game objects in the temporal_to_delete vector from the scene.
    // Append to the vector using Delete(string name).
    // This does not delete the object itself, since it might be needed to Instantiate a new version.
    void DeleteObjects();

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

    // Lookup table for all game objects by name, only used for prefabs and lookup by name.
    unordered_map<string, GameObject*> name_objects;

    // Vector that stores all game objects added in AddNewObject().
    // Appends these objects to the relevant vectors and maps before all game objects are updated in the next frame.
    vector<GameObject*> temporal_objects;

    // Vector that stores all game objects that were "deleted" this frame.
    vector<string> temporal_to_delete;

    // Stores the number of clones that have been created using Instantiate().
    // Used to avoid duplicate naming.
    unordered_map<string, int> clone_version;
};

#endif
