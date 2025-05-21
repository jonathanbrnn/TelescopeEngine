#ifndef FORCE_H
#define FORCE_H

#include <iostream>

using namespace std;

enum ForceMode {
    // constant force
    LINEAR,
    // start weak and increase or start strong and decrease
    QUADRATIC_EASE_IN,
    QUADRATIC_EASE_OUT,
};

enum ForceAxis {
    AXIS_X,
    AXIS_Y,
    AXIS_BOTH
};

class Force {
    public:
    float initial_force;
    float current_force = 0;
    float last_frame_force;

    float elapsed_time = 0;
    float duration;

    ForceMode update_mode;
    ForceAxis axis;

    Force(float initial_force, float duration, ForceMode update_mode, ForceAxis axis = AXIS_BOTH);

    void UpdateForce(float delta_time);
};

#endif
