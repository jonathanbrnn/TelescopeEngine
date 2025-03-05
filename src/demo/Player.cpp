#include "Player.h"
#include <iostream>
#include <random>

using namespace std; 

void Player::Start() {
    managerHub = &ManagerHub::GetInstance();
    AddBody(1, true);
    AddCollider();

    TextureManager* textureManager = &TextureManager::GetInstance(); 

    for (string frame : frames) {
        textureManager->LoadTexture(frame, renderer);
    }
}

void Player::Update() {
    bool is_walking = false; 

    if (body->dx != 0) {
        is_walking = true; 
    }
    else {
        is_walking = false; 
    }

    if (is_walking) {
        frame_delay += 1;
        if (frame_delay % 5 == 0 ) {
            Animate();
            frame_delay = 0;
        }
    }

    int horizontal = managerHub->inputManager->IsPressedDown("Horizontal"); 
    
    if (horizontal != 0) {
        body->SetVelocity(horizontal, 0); 
    }
    else {
        body->SetVelocity(0, 0);
    }

    if (managerHub->inputManager->IsPressedDown("Space") != 0) {
        CreateHeart();
    }
}

void Player::OnCollision(Collision collision) {
    // Prevent falling
    if (collision.collision_side == BOTTOM && pos_y + body->dy > pos_y) {
        body->SetVelocity(body->dx, 0);
    }
}

void Player::Whisper(int code) {
    switch (code) {
        case 1: 
        CreateHeart(); 
        break;
        case 2: 
        ResetPosition();
        break;
    }
}

// This is a mockup animator not intended as an actual feature: 

void Player::Animate() {
    current_frame += 1;

    if (current_frame >= frames.size()) {
        current_frame = 0;
    }

    texture = TextureManager::GetInstance().LoadTexture(frames[current_frame], renderer); 
}

void Player::CreateHeart() {
    random_device rd;  
    mt19937 gen(rd()); 
    uniform_int_distribution<int> dist(50, 200);

    int scale = dist(gen);
    Heart* clone = new Heart(renderer, "Heart", pos_x + (width / 2), pos_y, 2, scale, scale, 0, "/Users/jonathan/TelescopeEngine/media/images/Heart-1.png");

    clone->Start(); 

    ManagerHub::GetInstance().entityManager->visible_objects[2].push_back(clone);
    ManagerHub::GetInstance().entityManager->body_objects.push_back(clone); 
    ManagerHub::GetInstance().entityManager->total_objects.push_back(clone);
}

void Player::ResetPosition() {
    SetPosition(100, 100);
}; 