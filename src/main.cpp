#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "demo/Player.h"
#include "demo/Heart.h"
#include "demo/Celestine.h"
#include "core/ManagerHub.h"
#include "core/EntityManager.h"
#include "core/TimeManager.h"
#include "core/Runtime.h"
#include "entities/Body.h"
#include "entities/Force.h"
#include "entities/GameObject.h"
#include "entities/CollisionManager.h"
#include "entities/TextureManager.h"
#include "input/InputManager.h"
#include <vector>
#include <map>


void InitializeEngine(SDL_Window*& window, SDL_Renderer*& renderer) {
    window = InitializeWindow(1440, 900);
    renderer = InitializeRenderer(window);

    EntityManager* entityManager = &EntityManager::GetInstance(renderer);

    TimeManager* timeManager = &TimeManager::GetInstance();

    CollisionManager* collisionManager = &CollisionManager::GetInstance();

    TextureManager* textureManager = &TextureManager::GetInstance();

    InputManager* inputManager = &InputManager::GetInstance();

    ManagerHub* managerHub = &ManagerHub::GetInstance();

    managerHub->OnStart(entityManager, timeManager, collisionManager, textureManager, inputManager);

    collisionManager->OnStart(&ManagerHub::GetInstance());
}

void closeEngine(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main() {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    ManagerHub* managerHub = &ManagerHub::GetInstance();

    InitializeEngine(window, renderer);

    Player player(renderer, "Jonathan", 450, 0, 0, 128, 128, 0, "/Users/admin/TelescopeEngine/media/images/PlayerRun1.png");
    GameObject ground(renderer, "Ground", -100, 804, -1, 2688, 96, 0, "/Users/admin/TelescopeEngine/media/images/ground.png");
    GameObject background(renderer, "Background", 0, 0, -2, 1440, 900, 0, "/Users/admin/TelescopeEngine/media/images/clouds_background.png");
    Celestine celestine(renderer, "Celestine", 620, 671, -2, 200, 133, 0, "/Users/admin/TelescopeEngine/media/images/Celestine.JPG");

    ground.AddCollider();

    vector<GameObject*> prefabs;

    prefabs.push_back(&player);
    prefabs.push_back(&ground);
    prefabs.push_back(&background);
    prefabs.push_back(&celestine);

    if (managerHub->entityManager != nullptr) {
        cout << "WOOOHOOO!" << endl;
    }

    managerHub->entityManager->OnStart(prefabs);

    cout << "ENTERING UPDATE!" << endl;
    UpdateAll(renderer);

    closeEngine(window, renderer);

    return 0;
}
