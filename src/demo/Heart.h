#ifndef HEART_H
#define HEART_H

#include <iostream>
#include "../entities/GameObject.h"
#include "../entities/TextureManager.h"

using namespace std;

class Heart : public GameObject {
    public:
    Heart(SDL_Renderer* renderer, string name, float pos_x = 0, float pos_y = 0, float pos_z = 0, float width = 1,
        float height = 1, float rotation = 0, string texture_filepath = "/Users/admin/TelescopeEngine/media/sample_640×426.bmp") : GameObject(renderer, name, pos_x, pos_y, pos_z, width, height, rotation, texture_filepath) {}

        void Start() override;
        void Update() override;
        void OnCollision(Collision collision) override;

        // You have to create a new body, animator & collider for the Clone method to work.
        // Due to your current use of pointers, the clone will refer back to the original components.
        Heart* Clone() const override { return new Heart(*this); }

        void Break();

    private:
        bool is_broken = false;
        vector<string> default_anim = {"/Users/admin/TelescopeEngine/media/images/Heart-1.png", "/Users/admin/TelescopeEngine/media/images/Heart-2.png", "/Users/admin/TelescopeEngine/media/images/Heart-3.png", "/Users/admin/TelescopeEngine/media/images/Heart-4.png"};
        vector<string> breaking_anim = {"/Users/admin/TelescopeEngine/media/images/Heart_breaking-1.png", "/Users/admin/TelescopeEngine/media/images/Heart_breaking-2.png", "/Users/admin/TelescopeEngine/media/images/Heart_breaking-3.png", "/Users/admin/TelescopeEngine/media/images/Heart_breaking-4.png", "/Users/admin/TelescopeEngine/media/images/Heart_breaking-5.png", "/Users/admin/TelescopeEngine/media/images/Heart_breaking-6.png", "/Users/admin/TelescopeEngine/media/images/Heart_breaking-7.png", "/Users/admin/TelescopeEngine/media/images/Heart_breaking-8.png", "/Users/admin/TelescopeEngine/media/images/Heart_breaking-9.png", "/Users/admin/TelescopeEngine/media/images/Heart_breaking-10.png", "/Users/admin/TelescopeEngine/media/images/Heart_breaking-10.png"};
};

#endif
