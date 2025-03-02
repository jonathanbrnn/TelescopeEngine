#include "Force.h"

Force::Force(float initial_force, float duration, ForceMode update_mode, ForceAxis axis) {
    this->initial_force = initial_force; 
    
    this->duration = duration; 

    this->update_mode = update_mode; 
    this->axis = axis; 
}