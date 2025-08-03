#include "Cell.h"

void Cell::SetState(int new_state) {
    if (new_state > 1) { new_state = 1; }
    if (new_state < 0) { new_state = 0; }

    current_state = new_state; 

    texture = managerHub->textureManager->LoadTexture(states[current_state], renderer); 
}

void Cell::FlipState() {
    if (current_state == 1) { current_state = 0; }
    else { current_state = 1; }

    texture = managerHub->textureManager->LoadTexture(states[current_state], renderer); 
}