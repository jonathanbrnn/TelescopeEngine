#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <SDL.h>

enum KeyPress {
    KEY_PRESS_DEFAULT, 
    KEY_PRESS_LEFT,
    KEY_PRESS_RIGHT, 
    KEY_PRESS_UP, 
    KEY_PRESS_DOWN,
    KEY_PRESS_SPACE,
    KEY_PRESS_ONE, 
    KEY_PRESS_TWO,
    KEY_PRESS_THREE
}; 

KeyPress HandleKeyPress(SDL_Keycode key); 

bool ListenForInput(SDL_Event event); 

#endif