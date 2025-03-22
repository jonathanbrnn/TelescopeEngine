#ifndef BODY_H
#define BODY_H

#include <iostream>

#include "Force.h"

using namespace std;

class Body {
    public:
    // The mass of the body. Used to calculate the change in velocity of the body based on all current forces.
    float mass = 1;

    // The velocity of the body.
    // The velocity calculated every frame and applied to the game objects position:
    float dx = 0;
    float dy = 0;
    // The base velocity of the body. Used to prevent accumulating force over time.
    float base_dx = 0;
    float base_dy = 0;

    // Wether or not gravity (a constant downward force on the y-axis) is applied to the body.
    bool use_gravity = true;
    float gravity_force = 5;

    // VELOCITY:
    // Set's the dx, dy, base_dx and base_dy of the object.
    // dx DEFAULT=NULL
    // dy DEFAULT=NULL
    void SetVelocityBothAxis(float dx, float dy);

    void SetDX(float dx);

    void SetDY(float dy);

    // Updates the velocity by calculating all active forces and then adding them to the body's dx and dy.
    // (!) must be passed the current delta time.
    void UpdateVelocity(float delta_time);

    // Deletes all expired forces at the end of each frame.
    void DeleteForces();

    // FORCE'S:
    // Add's a new force to the forces vector. Used to apply a new force to the body.
    // update_mode determines the way the intensity of the force changes during it's lifetime (DEFAULT=LINEAR).
    // axis determines the axis on which force is applied to (DEFAULT=AXIS_BOTH).
    void ApplyForce(float initial_force, float duration, ForceMode update_mode = LINEAR, ForceAxis axis = AXIS_BOTH);

    // CONSTRUCTOR:
    // mass DEFAULT=1
    // use_gravity DEFAULT=true
    Body(float mass = 1, bool use_gravity = true);

    private:
    // Stores all active forces.
    vector<Force*> forces;

    // Stores the indices of all forces that have expired this frame.
    // Used to delete the forces at the end of the frame.
    vector<int> expired_forces_indices;
};
#endif
