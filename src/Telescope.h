#ifndef TELESCOPE_H 
#define TELESCOPE_H

#include "dependencies.h"

#include "core/ManagerHub.h"
#include "core/EntityManager.h"
#include "core/Loop.h"
#include "core/GameLoop.h"
#include "core/EditorLoop.h"
#include "core/TimeManager.h"
#include "entities/Body.h"
#include "entities/Force.h"
#include "entities/GameObject.h"
#include "entities/CollisionManager.h"
#include "entities/TextureManager.h"
#include "input/InputManager.h"
#include "rendering/Camera.h"
#include "rendering/Renderer.h"
#include "rendering/GameRenderer.h"
#include "rendering/EditorRenderer.h"
#include "utilities/BaseObject.h"

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

//#include <nlohmann/json.hpp>
//using json = nlohmann::json; 

using namespace std; 

enum Mode {
    EDITOR, 
    GAME
}; 

class Engine {
    public: 
    static Engine& GetInstance() {
        static Engine instance; 
        return instance; 
    }

    void Entry(vector<GameObject*> prefabs);

    void Runtime(); 

    void Exit(); 

    Mode Get_Mode(); 

    private: 

    ManagerHub* managerHub = nullptr; 

    Loop* loop = nullptr; 

    Mode mode = GAME; 


    bool use_vsync = true; 
    bool fullscreen = false; 
    
    string window_title = "TelescopeEngine"; 

    int screen_width = 1440; 
    int screen_height = 900; 

    int window_pos_x = 0; 
    int window_pos_y = 0; 

    bool running = false; 

    Engine(const Engine&) = delete; 
    Engine& operator=(const Engine&) = delete; 

    explicit Engine() {}
}; 

#endif 