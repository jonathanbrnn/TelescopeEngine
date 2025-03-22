#ifndef SPIKES_H
#define SPIKES_H

#include "../entities/GameObject.h"

using namespace std;

class Spikes : public GameObject {
    public:
    Spikes(SDL_Renderer* renderer, string name, float pos_x = 0, float pos_y = 0, float pos_z = 0, float width = 1,
            float height = 1, float rotation = 0, string texture_filepath = "/Users/admin/TelescopeEngine/media/sample_640×426.bmp") : GameObject(renderer, name, pos_x, pos_y, pos_z, width, height, rotation, texture_filepath) {}

    void Start() override;
    void Update() override;
    void OnCollision(Collision collision) override;

    private:
    int speed = 1;
    bool is_idle = true;

    int played_idle = 5;

    vector<string> idle = {"/Users/admin/TelescopeEngine/media/images/spikes-idle-1.png", "/Users/admin/TelescopeEngine/media/images/spikes-idle-2.png", "/Users/admin/TelescopeEngine/media/images/spikes-idle-3.png", "/Users/admin/TelescopeEngine/media/images/spikes-idle-4.png", "/Users/admin/TelescopeEngine/media/images/spikes-idle-4.png"};
    vector<string> walking = {"/Users/admin/TelescopeEngine/media/images/spikes-walking-1.png", "/Users/admin/TelescopeEngine/media/images/spikes-walking-2.png", "/Users/admin/TelescopeEngine/media/images/spikes-walking-3.png", "/Users/admin/TelescopeEngine/media/images/spikes-walking-4.png", "/Users/admin/TelescopeEngine/media/images/spikes-walking-5.png"};

};

#endif
