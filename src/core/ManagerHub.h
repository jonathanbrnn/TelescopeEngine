#ifndef MANAGERHUB_H
#define MANAGERHUB_H

#include "EntityManager.h"
#include "TimeManager.h"
#include "../entities/CollisionManager.h"
#include "../entities/TextureManager.h"
#include "../input/InputManager.h"
#include "../rendering/Camera.h"

class Camera;

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

    void OnStart(Camera* camera, EntityManager* entityManager, TimeManager* timeManager, CollisionManager* collisionManager, TextureManager* textureManager, InputManager* inputManager);

    Camera* camera;
    EntityManager* entityManager;
    TimeManager* timeManager;
    CollisionManager* collisionManager;
    TextureManager* textureManager;
    InputManager* inputManager;

private:
    // Private constructor ensures no external instantiation
    explicit ManagerHub() {}
};

#endif
