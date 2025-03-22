#include "Body.h"
#include "Force.h"

Body::Body(float mass, bool use_gravity) {
    this->mass = mass;
    this->use_gravity = use_gravity;

    if (this->use_gravity) {
        // gravity_force = mass * storage.gravity_constant;
    }
}

void Body::SetVelocityBothAxis(float dx, float dy) {
    base_dx = dx;
    this->dx = dx;

    base_dy = dy;
    this->dy = dy;
}

void Body::SetDX(float dx) {
    base_dx = dx;
    this->dx = dx;
}

void Body::SetDY(float dy) {
    base_dy = dy;
    this->dy = dy;
}

void Body::UpdateVelocity(float delta_time) {
    dx = base_dx;
    dy = base_dy;

    for (int i = 0; i < forces.size(); i++) {
        Force* force = forces[i];
        force->UpdateForce(delta_time);

        if (force->duration <= force->elapsed_time) {
            expired_forces_indices.push_back(i);
        }

        if (force->axis == AXIS_X || force->axis == AXIS_BOTH) {
            dx += force->current_force;
        }
        if (force->axis == AXIS_Y || force->axis == AXIS_BOTH) {
            dy += force->current_force;
        }
    }

    if (use_gravity) {
        dy += gravity_force;
    }

    DeleteForces();
}

void Body::DeleteForces() {
    for (int i = expired_forces_indices.size() - 1; i >= 0; i--) {
        int index = expired_forces_indices[i];
        Force* to_delete = forces[index];
        forces.erase(forces.begin() + index);
        delete to_delete;
    }

    expired_forces_indices.clear();
}

void Body::ApplyForce(float initial_force, float duration, ForceMode update_mode, ForceAxis axis) {
    Force* new_force = new Force(initial_force, duration, update_mode, axis);
    forces.push_back(new_force);
}
