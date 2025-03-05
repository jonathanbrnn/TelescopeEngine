#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <SDL.h>
#include <map>

using namespace std; 

class InputManager {
    public: 
    InputManager(const InputManager&) = delete; 
    InputManager& operator=(const InputManager&) = delete; 
    static InputManager& GetInstance() {
        static InputManager instance; 
        return instance;
    }; 

    void UpdateInput(SDL_Event& event); 

    // Returns wether or not a key is currently being pressed or held down (0 = not pressed, !0 = pressed).
    //
    // Special case "Horizontal" and "Vertical"
    // "Horizontal" ("A", "D", "Left", "Right") and "Vertical" ("W", "S", "Up", "Down"). 
    // Returns -1 for "Horizontal" ("A", "Left") and "Vertical" ("W", "Up") and 1 for "Horizontal" ("D", "Right") and "Vertical" ("S", "Down").
    int IsPressedDown(string key); 

    private: 
    explicit InputManager() {} 

    map<string, bool> key_states = {
        {"Escape", false}, {"^", false}, {"1", false}, {"2", false}, {"3", false}, {"4", false}, {"5", false}, 
        {"6", false}, {"7", false}, {"8", false}, {"9", false}, {"0", false}, {"ß", false}, {"´", false}, 
        {"Backspace", false}, {"Tab", false}, {"Q", false}, {"W", false}, {"E", false}, {"R", false}, {"T", false}, 
        {"Z", false}, {"U", false}, {"I", false}, {"O", false}, {"P", false}, {"ü", false}, {"+", false}, 
        {"Return", false}, {"CapsLock", false}, {"A", false}, {"S", false}, {"D", false}, {"F", false}, {"G", false}, 
        {"H", false}, {"J", false}, {"K", false}, {"L", false}, {"ö", false}, {"ä", false}, {"#", false}, 
        {"Left Shift", false}, {"<", false}, {"Y", false}, {"X", false}, {"C", false}, {"V", false}, {"B", false}, 
        {"N", false}, {"M", false}, {",", false}, {".", false}, {"-", false}, {"Right Shift", false}, 
        {"Left Ctrl", false}, {"Left Option", false}, {"Left Command", false}, {"Space", false}, 
        {"Right Command", false}, {"Right Option", false}, {"Left", false}, {"Up", false}, {"Down", false}, {"Right", false}
    };
};

#endif