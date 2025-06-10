#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <SDL.h>
#include <map>
#include <iostream>

#include "../core/ManagerHub.h"

class ManagerHub; 

using namespace std;

class InputManager {
    public:
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;
    static InputManager& GetInstance() {
        static InputManager instance;
        return instance;
    };

    void OnStart(ManagerHub* managerHub); 

    void ResetIsPressed();

    void UpdateInputManager(SDL_Event& event);

    // Returns wether or not a key is currently being pressed or held down (0 = not pressed, !0 = pressed).
    //
    // Special case "Horizontal" and "Vertical"
    // "Horizontal" ("A", "D", "Left", "Right") and "Vertical" ("W", "S", "Up", "Down").
    // Returns -1 for "Horizontal" ("A", "Left") and "Vertical" ("W", "Up") and 1 for "Horizontal" ("D", "Right") and "Vertical" ("S", "Down").
    int IsPressedDown(string key);

    // Returns wether or not a key is currently being pressed (0 = not pressed. !0 = pressed). Does not register again if the user is holding the key down.
    //
    // Special case "Horizontal" and "Vertical"
    // "Horizontal" ("A", "D", "Left", "Right") and "Vertical" ("W", "S", "Up", "Down").
    // Returns -1 for "Horizontal" ("A", "Left") and "Vertical" ("W", "Up") and 1 for "Horizontal" ("D", "Right") and "Vertical" ("S", "Down").
    int IsPressed(string key);

    // Copies the current mouse position in world space. 
    void GetMousePosition(int& mouse_pos_x, int& mouse_pos_y);

    private:
    explicit InputManager() {}

    // KEYBOARD & MOUSE 
    // Keeps track of all key states. Returns true if a key is pressed or held down, false otherwise.
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
        {"Right Command", false}, {"Right Option", false}, {"Left", false}, {"Up", false}, {"Down", false}, {"Right", false},
        {"Mouse Left", false}, {"Mouse Middle", false}, {"Mouse Right", false}
    };

    // Holds all keys that were pressed during the current frame. Is reset at the start of each frame.
    map<string, bool> current_frame_keys;

    // Keeps track of the mouse position. 
    int mouse_pos_x; 
    int mouse_pos_y; 

    ManagerHub* managerHub; 
};

#endif
