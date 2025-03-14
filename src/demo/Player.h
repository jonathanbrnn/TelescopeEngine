#ifndef PLAYER_H
#define PLAYER_H

#include "../entities/GameObject.h"
#include "../core/ManagerHub.h"
#include "Heart.h"
#include <iostream>
#include <random>

using namespace std;

class Player : public GameObject {
    public:
    Player(SDL_Renderer* renderer, string name, float pos_x = 0, float pos_y = 0, float pos_z = 0, float width = 1,
        float height = 1, float rotation = 0, string texture_filepath = "/Users/admin/TelescopeEngine/media/sample_640×426.bmp") : GameObject(renderer, name, pos_x, pos_y, pos_z, width, height, rotation, texture_filepath) {}

        void Start() override;
        void Update() override;
        void OnCollision(Collision collision) override;
        void Whisper(int code) override;

        void Animate();
        void CreateHeart();
        void ResetPosition();
        void Jump();

    private:
    vector<Heart*> hearts;
    int current_heart;

    bool is_grounded;
    bool is_jumping;

    vector<string> idle = {"/Users/admin/TelescopeEngine/media/images/Heart-1.png", "/Users/admin/TelescopeEngine/media/images/Heart-2.png", "/Users/admin/TelescopeEngine/media/images/Heart-3.png", "/Users/admin/TelescopeEngine/media/images/Heart-4.png"};
    vector<string> walking = {"/Users/admin/TelescopeEngine/media/images/PlayerRun1.png", "/Users/admin/TelescopeEngine/media/images/PlayerRun2.png", "/Users/admin/TelescopeEngine/media/images/PlayerRun3.png", "/Users/admin/TelescopeEngine/media/images/PlayerRun4.png",
"/Users/admin/TelescopeEngine/media/images/PlayerRun5.png", "/Users/admin/TelescopeEngine/media/images/PlayerRun6.png", "/Users/admin/TelescopeEngine/media/images/PlayerRun7.png", "/Users/admin/TelescopeEngine/media/images/PlayerRun8.png", "/Users/admin/TelescopeEngine/media/images/PlayerRun9.png", "/Users/admin/TelescopeEngine/media/images/PlayerRun10.png"};
    vector<string> wave = {"/Users/admin/TelescopeEngine/media/images/PlayerWave1.png", "/Users/admin/TelescopeEngine/media/images/PlayerWave2.png", "/Users/admin/TelescopeEngine/media/images/PlayerWave3.png", "/Users/admin/TelescopeEngine/media/images/PlayerWave4.png", "/Users/admin/TelescopeEngine/media/images/PlayerWave5.png"};
};

#endif
