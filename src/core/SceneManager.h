#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "ManagerHub.h"

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include <filesystem>
namespace fs = std::filesystem;

using namespace std; 

struct Blueprint {
    string name; 
    string heritage; 
    float pos_x; 
    float pos_y; 
    float pos_z; 
    float rotation; 
    float width; 
    float height; 

    Blueprint(string name, string heritage, float pos_x, float pos_y, float pos_z, float rotation, float width, float height) {
        name = name; 
        heritage = heritage; 
        pos_x = pos_x; 
        pos_y = pos_y; 
        pos_z = pos_z; 
        rotation = rotation; 
        width = width; 
        height = height;
    }
};  

class SceneManager {
    public: 
    static SceneManager& GetInstance() {
        static SceneManager instance; 
        return instance; 
    }

    void OnStart(int mode);

    void LoadScene(string scene_name); 

    void SaveScene(string scene_name); 

    // void SaveData(string key, string val); 

    // LOADSCENE 
    // SAVESCENE 
    // SAVEDATATOOBJECT 
    /*

    */

    private: 
    unordered_map<string, vector<Blueprint*>> known_scenes; 

    const string scenes_filepath = "/Users/jonathan/TelescopeEngine/scenes/"; 

    ManagerHub* managerHub = nullptr; 

    // 0 = GAME, 1 = EDITOR, cant be bothered with these pesky circular dependencies. 
    int mode = 0;     

    SceneManager() {}

    SceneManager(const SceneManager&) = delete; 
    SceneManager& operator=(const SceneManager&) = delete; 

    ~SceneManager() {
        known_scenes.clear(); 
    }
}; 

#endif 