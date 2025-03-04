#ifndef HEART_H
#define HEART_H

#include <iostream>
#include "../entities/GameObject.h"
#include "../entities/TextureManager.h"

using namespace std;

class Heart : public GameObject {
    public: 
    Heart(SDL_Renderer* renderer, string name, float pos_x = 0, float pos_y = 0, float pos_z = 0, float width = 1, 
        float height = 1, float rotation = 0, string texture_filepath = "/Users/jonathan/TelescopeEngine/media/sample_640×426.bmp") : GameObject(renderer, name, pos_x, pos_y, pos_z, width, height, rotation, texture_filepath) {}

        void Start() override; 
        void Update() override;
        void OnCollision(Collision collision) override;

        void Animate(); 

    private: 
        int frame_delay = 0;
        int current_frame = -1; 
        vector<string> frames = {"/Users/jonathan/TelescopeEngine/media/images/Heart-1.png", "/Users/jonathan/TelescopeEngine/media/images/Heart-2.png", "/Users/jonathan/TelescopeEngine/media/images/Heart-3.png", "/Users/jonathan/TelescopeEngine/media/images/Heart-4.png"};
};

#endif