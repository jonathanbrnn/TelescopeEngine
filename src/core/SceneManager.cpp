#include "SceneManager.h"

void SceneManager::LoadScene(string scene_name) {
    string scene_filepath = scenes_filepath + scene_name + ".json"; 

    if (known_scenes.find(scene_name) != known_scenes.end()) {
        EntityManager* entityManager = managerHub->entityManager; 
        for (auto game_object : entityManager->total_objects) {
            entityManager->Delete(game_object->name); 
        }

        for (auto blueprint : known_scenes[scene_name]) {
            entityManager->Instantiate(blueprint->heritage, blueprint->name, blueprint->pos_x, blueprint->pos_y, blueprint->pos_z, blueprint->width, blueprint->height); 
        }
    }
    else if (fs::exists(scenes_filepath)) {
        EntityManager* entityManager = managerHub->entityManager; 
        // Delete all active game objects in the current scene
        for (auto game_object : entityManager->total_objects) {
            entityManager->Delete(game_object->name); 
        }
        
        ifstream in_file(scene_filepath); 
        nlohmann::json json; 
        in_file >> json; 
        in_file.close(); 

        for (auto object : json["objects"]) {
            string name = object["name"]; 
            string heritage = object["heritage"]; 
            float pos_x = object["pos_x"]; 
            float pos_y = object["pos_y"]; 
            float pos_z = object["pos_z"]; 
            float rotation = object["rotation"]; 
            float width = object["width"]; 
            float height = object["height"]; 

            entityManager->Instantiate(heritage, name, pos_x, pos_y, pos_z, rotation, width, height); 
        }
    }
    else {
        cout << "SCENEMANAGER: Could not load scene: " << scene_name << " because the scenes file could not be found." << endl; 
    }
}

// IMPLEMENTED FOR EDITOR USE ONLY
void SceneManager::SaveScene(string scene_name) {
    if (mode != 1) {
        cout << "SCENEMANAGER: SceneManager::SaveScene() is only meant to be used from the editor!" << endl; 
        return; 
    }
    if (fs::exists(scenes_filepath)) {
        EntityManager* entityManager = managerHub->entityManager; 
        vector<GameObject*> active_objects = entityManager->total_objects;

        nlohmann::json json; 
        
        for (auto game_object : active_objects) {
            json["objects"] = {
                {"name" , game_object->name}, 
                {"heritage" , game_object->heritage},
                {"pos_x" , game_object->pos_x},
                {"pos_y" , game_object->pos_y}, 
                {"pos_z" , game_object->pos_z}, 
                {"rotation" , game_object->rotation},
                {"width" , game_object->width}, 
                {"height" , game_object->height} 
            }; 
        }

        ofstream out_file(scenes_filepath + scene_name + ".json"); 

        if (!out_file) {
            cout << "SCENEMANAGER: Could not save scene: " << scene_name << ". File could not be opened for writing!" << endl; 
        }
        else {
            out_file << json.dump(4);
            out_file.close();   
        }
    }
    else {
        cout << "SCENEMANAGER: Could not save scene: " << scene_name << " because the scenes file could not be found." << endl; 
    }

    cout << "SCENEMANAGER: Scene: " << scene_name << " was successfuly saved!" << endl; 
}