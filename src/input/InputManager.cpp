#include "InputManager.h"

using namespace std;

void InputManager::OnStart(ManagerHub* managerHub) {
    this->managerHub = managerHub; 
}

void InputManager::ResetIsPressed() {
    current_frame_keys.clear();
}

void InputManager::UpdateInputManager(SDL_Event& event) {
    Uint32 mouse_state = SDL_GetMouseState(&mouse_pos_x, &mouse_pos_y); 

    key_states["Mouse Left"] = mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT);
    key_states["Mouse Middle"] = mouse_state & SDL_BUTTON(SDL_BUTTON_MIDDLE);
    key_states["Mouse Right"] = mouse_state & SDL_BUTTON(SDL_BUTTON_RIGHT);

    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
        string key_name = SDL_GetKeyName(event.key.keysym.sym);

        if (event.type == SDL_KEYDOWN) {
            key_states[key_name] = true;
            current_frame_keys[key_name] = true;
        }
        else if (event.type == SDL_KEYUP) {
            key_states[key_name] = false;
        }
    }

    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT)
            current_frame_keys["Mouse Left"] = true;
        else if (event.button.button == SDL_BUTTON_MIDDLE)
            current_frame_keys["Mouse Middle"] = true;
        else if (event.button.button == SDL_BUTTON_RIGHT)
            current_frame_keys["Mouse Right"] = true;
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

int InputManager::IsPressed(string key) {
    if (current_frame_keys[key]) {
        if (key == "Horizontal") {
            if (current_frame_keys["A"] || current_frame_keys["Left"]) {
                current_frame_keys[key] = false;
                return -1;
            }
            if (current_frame_keys["D"] || current_frame_keys["Right"]) {
                current_frame_keys[key] = false;
                return 1;
            }
        }
        else if (key == "Vertical") {
            if (current_frame_keys["W"] || current_frame_keys["Up"]) {
                current_frame_keys[key] = false;
                return -1;
            }
            if (current_frame_keys["S"] || current_frame_keys["Down"]) {
                current_frame_keys[key] = false;
                return 1;
            }
        }

        current_frame_keys[key] = false;
        return 1;
    }

    current_frame_keys[key] = false;
    return 0;
}

void InputManager::GetMousePosition(int& mouse_pos_x, int& mouse_pos_y) {
    mouse_pos_x = this->mouse_pos_x + managerHub->camera->x; 
    mouse_pos_y = this->mouse_pos_y + managerHub->camera->y; 
}
