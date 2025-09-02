#ifndef HEART_H
#define HEART_H

#include <iostream>
#include "../../src/entities/GameObject.h"

using namespace std;

class Heart : public GameObject {
    public:
    Heart(string name, float pos_x = 0, float pos_y = 0, float pos_z = 0, float width = 1,
        float height = 1, float rotation = 0, string texture_filepath = "../../media/default_grid.png") : GameObject(name, pos_x, pos_y, pos_z, width, height, rotation, texture_filepath) {}

        void Start() override;
        void Update() override;
        void OnCollision(Collision collision) override;

        Heart* Clone() const override { return new Heart(*this); }

        void Break();
    private:
    bool is_broken = false;
    vector<string> default_anim = {
        "/Users/jonathan/TelescopeEngine/media/images/Heart-1.png",
        "/Users/jonathan/TelescopeEngine/media/images/Heart-2.png",
        "/Users/jonathan/TelescopeEngine/media/images/Heart-3.png",
        "/Users/jonathan/TelescopeEngine/media/images/Heart-4.png"
    };
    vector<string> breaking_anim = {
        "/Users/jonathan/TelescopeEngine/media/images/Heart_breaking-1.png",
        "/Users/jonathan/TelescopeEngine/media/images/Heart_breaking-2.png",
        "/Users/jonathan/TelescopeEngine/media/images/Heart_breaking-3.png",
        "/Users/jonathan/TelescopeEngine/media/images/Heart_breaking-4.png",
        "/Users/jonathan/TelescopeEngine/media/images/Heart_breaking-5.png",
        "/Users/jonathan/TelescopeEngine/media/images/Heart_breaking-6.png",
        "/Users/jonathan/TelescopeEngine/media/images/Heart_breaking-7.png",
        "/Users/jonathan/TelescopeEngine/media/images/Heart_breaking-8.png",
        "/Users/jonathan/TelescopeEngine/media/images/Heart_breaking-9.png",
        "/Users/jonathan/TelescopeEngine/media/images/Heart_breaking-10.png",
        "/Users/jonathan/TelescopeEngine/media/images/Heart_breaking-10.png"
    };
};

#endif
