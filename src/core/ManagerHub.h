#ifndef MANAGERHUB_H
#define MANAGERHUB_H

#include "../dependencies.h"

#include "EntityManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "../entities/CollisionManager.h"
#include "../entities/TextureManager.h"
#include "../input/InputManager.h"
#include "../rendering/Camera.h"
#include "../rendering/Renderer.h"

class Renderer; 
class Camera;
class InputManager; 
class TextureManager;
class SceneManager;  

class ManagerHub {
public:
    // Deleted copy constructor and assignment operator to prevent duplicates
    ManagerHub(const ManagerHub&) = delete;
    ManagerHub& operator=(const ManagerHub&) = delete;

    // Static method to get the single instance
    static ManagerHub& GetInstance() {
        static ManagerHub instance;
        return instance;
    }

    void OnStart(Renderer* renderer, Camera* camera, EntityManager* entityManager, TimeManager* timeManager, SceneManager* sceneManager, CollisionManager* collisionManager, TextureManager* textureManager, InputManager* inputManager);
    void SetStorage(int screen_width, int screen_height); 

    Renderer* renderer; 
    Camera* camera;
    EntityManager* entityManager;
    TimeManager* timeManager;
    SceneManager* sceneManager; 
    CollisionManager* collisionManager;
    TextureManager* textureManager;
    InputManager* inputManager;

    // Returns the screen width, returns -1 if the screen width is not available.
    int Get_Screen_Width(); 
    int Get_Screen_Height();

    ~ManagerHub(); 
    
private:
    int screen_width; 
    int screen_height; 

    // Is set to true once the SetStore() function executed. 
    bool storage_set = false; 

    // Private constructor ensures no external instantiation
    explicit ManagerHub() {}
};

#endif
