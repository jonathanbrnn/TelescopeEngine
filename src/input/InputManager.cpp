#include "InputManager.h"

using namespace std; 

void InputManager::UpdateInput(SDL_Event& event) {
    string key_name = SDL_GetKeyName(event.key.keysym.sym);

    if (event.type == SDL_KEYDOWN) {        
        key_states[key_name] = true;
    }
    else if (event.type == SDL_KEYUP) {
        key_states[key_name] = false;
    }
}

int InputManager::IsPressedDown(string key) {
    if (key == "Horizontal") {
        if (key_states["A"] || key_states["Left"]) {
            return -1; 
        }
        if (key_states["D"] || key_states["Right"]) {
            return 1;
        }
    }
    
    if (key == "Vertical") {
        if (key_states["W"] || key_states["Up"]) {
            return -1; 
        }
        else if (key_states["S"] || key_states["Down"]) {
            return 1; 
        }
    }

    if (key_states[key]) {
        return 1; 
    }
    return 0;
}