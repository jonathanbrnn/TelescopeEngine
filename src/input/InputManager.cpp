#include <SDL.h>
#include "InputManager.h"
#include <unordered_map>

using namespace std; 

KeyPress HandleKeyPress(SDL_Keycode key) {
    switch (key) {
        case SDLK_w:
        case SDLK_UP: return KEY_PRESS_UP; 
        case SDLK_s: 
        case SDLK_DOWN: return KEY_PRESS_DOWN; 
        case SDLK_a:
        case SDLK_LEFT: return KEY_PRESS_LEFT; 
        case SDLK_d:
        case SDLK_RIGHT: return KEY_PRESS_RIGHT; 
        case SDLK_SPACE: return KEY_PRESS_SPACE; 
        default: return KEY_PRESS_DEFAULT;  
    }
}

bool ListenForInput(SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
        return true; 
    }
    return false; 
}

/*
class InputManager {
    public: 
    static InputManager& GetInstance() {
        static InputManager instance; 
        return instance; 
    }

    KeyPress HandleKeyPress(SDL_Keycode key) {
        switch (key) {
            case SDLK_w:
            case SDLK_UP: return KEY_PRESS_UP; 
            case SDLK_s: 
            case SDLK_DOWN: return KEY_PRESS_DOWN; 
            case SDLK_a:
            case SDLK_LEFT: return KEY_PRESS_LEFT; 
            case SDLK_d:
            case SDLK_RIGHT: return KEY_PRESS_RIGHT; 
            case SDLK_SPACE: return KEY_PRESS_SPACE; 
            default: return KEY_PRESS_DEFAULT;  
        }
    }

    bool ListenForInput(SDL_Event event) {
        if (event.type == SDL_KEYDOWN) {
            return true; 
        }
        return false; 
    }

    private: 
    InputManager() {}
    ~InputManager() {}

    unordered_map<SDL_Keycode, bool> isPressed; 
};
*/
