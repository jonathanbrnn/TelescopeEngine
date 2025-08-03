#include "dependencies.h"
#include "demo/Player.h"
#include "demo/Heart.h"
#include "demo/Celestine.h"
#include "demo/Spikes.h"

#include "demo/Grid.h"

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

#include <iostream>
#include <fstream>

//#include <nlohmann/json.hpp>

//using json = nlohmann::json;


#include <vector>
#include <map>


void InitializeEngine(SDL_Window*& window, SDL_Renderer*& renderer, int screen_width = 1440, int screen_height = 900) {
    window = InitializeWindow(screen_width, screen_height);
    renderer = InitializeRenderer(window, true);

    Camera* camera = new Camera(screen_width, screen_height);

    EntityManager* entityManager = &EntityManager::GetInstance(renderer);

    TimeManager* timeManager = &TimeManager::GetInstance();

    CollisionManager* collisionManager = &CollisionManager::GetInstance();

    TextureManager* textureManager = &TextureManager::GetInstance();

    InputManager* inputManager = &InputManager::GetInstance();

    ManagerHub* managerHub = &ManagerHub::GetInstance();


    managerHub->OnStart(camera, entityManager, timeManager, collisionManager, textureManager, inputManager);

    managerHub->SetStorage(screen_width, screen_height, renderer);

    camera->StartCamera(&ManagerHub::GetInstance());

    collisionManager->OnStart(&ManagerHub::GetInstance());

    inputManager->OnStart(&ManagerHub::GetInstance()); 
}

void closeEngine(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

/*
void json_test() {
    using json = nlohmann::json;
    std::string scene_name = "test_scene";

    json scene = {
        {"id", "test_scene"},
        {"objects", json::array({
            {
                {"name", "Player"},
                {"position", {100, 100, 0}}
            },
            {
                {"name", "ground"},
                {"position", {0, 0, 0}}
            }
        })}
    };

    ofstream out("../scenes/scenes.json");
    if (out.is_open()) {
        out << scene.dump(4); 
        out.close();
    }

    ifstream in("../scenes/scenes.json"); 
    if (in.is_open()) {
        json data;
        in >> data; 
        in.close(); 
        cout << "This is a test" << endl; 
        cout << data["objects"]["Player"]["position"][0];
    }
}
*/

int main() {
    //json_test(); 

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    ManagerHub* managerHub = &ManagerHub::GetInstance();

    InitializeEngine(window, renderer, 1440, 900);


    /*
    Player* player = new Player(renderer, "Jonathan", 450, 0, 0, 128, 128, 0, "../media/images/PlayerRun1.png");
    BaseObject* ground_left = new BaseObject(renderer, "ground_left", 0, 366, -1, 221, 534, 0, "../media/images/ground_left.png");
    BaseObject* ground_right_bottom = new BaseObject(renderer, "ground_right_bottom", 950, 717, -1, 187, 183, 0, "../media/images/ground_right_bottom.png");
    BaseObject* ground_right_top = new BaseObject(renderer, "ground_right_top", 977, 672, -1, 463, 228, 0, "../media/images/ground_right_top.png");
    BaseObject* background = new BaseObject(renderer, "background", 0, 0, -2, 1440, 900, 0, "../media/images/background_white.png");
    Spikes* spikes = new Spikes(renderer, "Spikes", 1200, 200, 0, 100, 55, 0, "../media/images/spikes-walking-1.png");

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
    
    */

    Grid* grid = new Grid(renderer, "Grid", 10000, 10000); 
    grid->SetCellThreshold(16); 

    vector<GameObject*> prefabs; 

    prefabs.push_back(grid); 

    if (managerHub->entityManager != nullptr) {
        cout << "WOOOHOOO!" << endl;
    }

    managerHub->entityManager->OnStart(prefabs);

    cout << "ENTERING UPDATE!" << endl;
    UpdateAll(renderer);

    closeEngine(window, renderer);

    return 0;
}
