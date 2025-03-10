#include "Player.h"
#include <iostream>

using namespace std; 

void Player::Start() {
    AddBody(1, true);
    AddCollider();

    TextureManager* textureManager = &TextureManager::GetInstance(); 

    for (string frame : frames) {
        textureManager->LoadTexture(frame, renderer);
    }
}

void Player::Update() {
    bool is_walking = body->dx != 0; 

    if (is_walking) {
        frame_delay += 1;
        if (frame_delay % 5 == 0 ) {
            Animate();
            frame_delay = 0;
        }
    }

    int horizontal = managerHub->inputManager->IsPressedDown("Horizontal"); 
    
    if (horizontal != 0) {
        body->SetVelocity(horizontal * 3, 0); 
    }
    else {
        body->SetVelocity(0, 0);
    }

    if (managerHub->inputManager->IsPressedDown("Space") != 0 && is_grounded && !is_jumping) {
        Jump();
    }

    if (managerHub->inputManager->IsPressedDown("H") != 0) {
        CreateHeart();
    }

    if (managerHub->inputManager->IsPressedDown("1") != 0) {
        ResetPosition();
    }
}

void Player::OnCollision(Collision collision) {
    // Prevent falling
    if (collision.collision_side == BOTTOM && pos_y + body->dy > pos_y && !is_jumping) {
        body->SetVelocity(body->dx, 0);
    }

    if (collision.collision_side == BOTTOM) {
        is_grounded = true; 
        is_jumping = false; 
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

    Heart* clone = new Heart(renderer, "Heart_clone", pos_x + (width / 2), pos_y, 2, scale, scale, 0, "/Users/jonathan/TelescopeEngine/media/images/Heart-1.png"); 

    managerHub->entityManager->AddNewObject(clone); 
}

void Player::ResetPosition() {
    SetPosition(100, 100);
}

void Player::Jump() {
    cout << "Trying to jump!" << endl;
    is_jumping = true;
    is_grounded = false;
    body->ApplyForce(-7, 0.1, QUADRATIC_EASE_OUT, AXIS_Y);
}