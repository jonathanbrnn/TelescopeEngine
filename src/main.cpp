#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "demo/Player.h"
#include "demo/Heart.h"
#include "demo/Celestine.h"
#include "demo/Spikes.h"
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
#include "rendering/Camera.h"
#include "utilities/BaseObject.h"

#include <vector>
#include <map>


void InitializeEngine(SDL_Window*& window, SDL_Renderer*& renderer) {
    window = InitializeWindow(1440, 900);
    renderer = InitializeRenderer(window, true);

    Camera* camera = new Camera(1440, 900);

    EntityManager* entityManager = &EntityManager::GetInstance(renderer);

    TimeManager* timeManager = &TimeManager::GetInstance();

    CollisionManager* collisionManager = &CollisionManager::GetInstance();

    TextureManager* textureManager = &TextureManager::GetInstance();

    InputManager* inputManager = &InputManager::GetInstance();

    ManagerHub* managerHub = &ManagerHub::GetInstance();


    managerHub->OnStart(camera, entityManager, timeManager, collisionManager, textureManager, inputManager);

    camera->StartCamera(&ManagerHub::GetInstance());

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

    Player* player = new Player(renderer, "Jonathan", 450, 0, 0, 128, 128, 0, "/Users/admin/TelescopeEngine/media/images/PlayerRun1.png");
    BaseObject* ground_left = new BaseObject(renderer, "ground_left", 0, 366, -1, 221, 534, 0, "/Users/admin/TelescopeEngine/media/images/ground_left.png");
    BaseObject* ground_right_bottom = new BaseObject(renderer, "ground_right_bottom", 950, 717, -1, 187, 183, 0, "/Users/admin/TelescopeEngine/media/images/ground_right_bottom.png");
    BaseObject* ground_right_top = new BaseObject(renderer, "ground_right_top", 977, 672, -1, 463, 228, 0, "/Users/admin/TelescopeEngine/media/images/ground_right_top.png");
    BaseObject* background = new BaseObject(renderer, "background", 0, 0, -2, 1440, 900, 0, "/Users/admin/TelescopeEngine/media/images/background_white.png");
    Spikes* spikes = new Spikes(renderer, "Spikes", 1200, 200, 0, 100, 55, 0, "/Users/admin/TelescopeEngine/media/images/spikes-walking-1.png");

    ground_left->AddCollider();
    ground_right_bottom->AddCollider();
    ground_right_top->AddCollider();

    vector<GameObject*> prefabs;

    prefabs.push_back(player);
    prefabs.push_back(ground_left);
    prefabs.push_back(ground_right_bottom);
    prefabs.push_back(ground_right_top);
    prefabs.push_back(background);
    prefabs.push_back(spikes);

    if (managerHub->entityManager != nullptr) {
        cout << "WOOOHOOO!" << endl;
    }

    managerHub->entityManager->OnStart(prefabs);

    cout << "ENTERING UPDATE!" << endl;
    UpdateAll(renderer);

    closeEngine(window, renderer);

    return 0;
}
