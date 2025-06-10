#ifndef COLLIDERVISUALIZER_H
#define COLLIDERVISUALIZER_H

#include "../entities/GameObject.h"

class ColliderVisualizer : public GameObject {
    ColliderVisualizer(SDL_Renderer* renderer, string name, float pos_x = 0, float pos_y = 0, float pos_z = 0, float width = 1,
        float height = 1, float rotation = 0, string texture_filepath = "../media/asesprite/collidervisualizer.png") : GameObject(renderer, name, pos_x, pos_y, pos_z, width, height, rotation, texture_filepath) {}

    void Update() override;

    ColliderVisualizer* Clone() const override { return new ColliderVisualizer(*this); }
};

#endif
