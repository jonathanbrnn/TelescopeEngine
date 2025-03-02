#ifndef PLAYER_H
#define PLAYER_H

#include "../entities/GameObject.h"

class Player : public GameObject {
    public:
    Player(SDL_Renderer* renderer, string name, float pos_x = 0, float pos_y = 0, float pos_z = 0, float width = 1, 
        float height = 1, float rotation = 0, string texture_filepath = "/Users/jonathan/TelescopeEngine/media/sample_640×426.bmp") : GameObject(renderer, name, pos_x, pos_y, pos_z, width, height, rotation, texture_filepath) {}

        void Start() override; 
        void Update() override;
        void OnCollision(Collision collision) override;
};

#endif