#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include "../entities/GameObject.h"

class BaseObject : public GameObject {
    public:
    BaseObject(SDL_Renderer* renderer, string name, float pos_x = 0, float pos_y = 0, float pos_z = 0, float width = 1,
        float height = 1, float rotation = 0, string texture_filepath = "../media/sample_640×426.bmp") : GameObject(renderer, name, pos_x, pos_y, pos_z, width, height, rotation, texture_filepath) {}

    BaseObject* Clone() const override { return new BaseObject(*this); }
};
#endif
