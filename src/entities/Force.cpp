#include "Force.h"

Force::Force(float initial_force, float duration, ForceMode update_mode, ForceAxis axis) {
    this->initial_force = initial_force;

    this->duration = duration;

    this->update_mode = update_mode;
    this->axis = axis;
}

void Force::UpdateForce(float deltaTime) {
    last_frame_force = current_force;

    elapsed_time += deltaTime;
    elapsed_time = min(elapsed_time, duration);

    switch (update_mode) {
        case LINEAR:
            current_force = initial_force * (1 - (elapsed_time / duration));
            break;

        case QUADRATIC_EASE_IN:
            current_force = initial_force * pow(elapsed_time / duration, 2);
            break;

        case QUADRATIC_EASE_OUT:
            current_force = initial_force * (1 - pow(elapsed_time / duration, 2));
            break;

        default:
            current_force = 0.0f;
            break;
    }

    if (elapsed_time >= duration) {
        current_force = 0.0f;
    }
}
