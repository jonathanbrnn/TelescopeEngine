#include "Player.h"
#include <iostream>
#include <vector>

using namespace std;

void Player::Start() {
    AddBody(1, true);
    AddCollider();
    AddAnimator();

    Heart* heart1 = new Heart(renderer, "Heart1", 30, 30, 2, 100, 100, 0, "/Users/admin/TelescopeEngine/media/images/Heart-1.png");
    Heart* heart2 = new Heart(renderer, "Heart2", 160, 30, 2, 100, 100, 0, "/Users/admin/TelescopeEngine/media/images/Heart-1.png");
    Heart* heart3 = new Heart(renderer, "Heart3", 290, 30, 2, 100, 100, 0, "/Users/admin/TelescopeEngine/media/images/Heart-1.png");

    managerHub->entityManager->AddNewObject(heart1);
    managerHub->entityManager->AddNewObject(heart2);
    managerHub->entityManager->AddNewObject(heart3);

    hearts.push_back(heart1);
    hearts.push_back(heart2);
    hearts.push_back(heart3);

    current_heart = hearts.size() - 1;

    // Add this objects animations.
    animator->AddState("idle", idle, 5);
    animator->AddState("walking", walking, 5);
    animator->AddState("wave", wave, 10);
}

void Player::Update() {
    bool is_walking = body->dx != 0;

    if (body->dx < 0) {
        FlipTexture(FLIP_HORIZONTAL, true);
    }
    else if (body->dx > 0) {
        flip_texture = false;
    }

    if (is_walking) {
        animator->SetState("walking");
    }
    else {
        animator->SetState("wave");
    }

    int horizontal = managerHub->inputManager->IsPressedDown("Horizontal");

    if (horizontal != 0) {
        body->SetDX(horizontal * 3);
    }
    else {
        body->SetDX(0);
    }

    if (managerHub->inputManager->IsPressedDown("Space") != 0 && is_grounded && !is_jumping) {
        Jump();
    }

    if (managerHub->inputManager->IsPressed("H") != 0) {
        CreateHeart();
    }

    if (managerHub->inputManager->IsPressedDown("1") != 0) {
        ResetPosition();
    }

    if (managerHub->inputManager->IsPressed("L") != 0) {
        animator->Stop();
    }

    if (managerHub->inputManager->IsPressed("O") != 0) {
        animator->Play();
    }

    if (managerHub->inputManager->IsPressed("P") != 0) {
        animator->PlayFrom("wave", 2);
    }

    if (managerHub->inputManager->IsPressed("T") != 0) {
        body->ApplyForce(1, 1.5);
    }

    if (managerHub->inputManager->IsPressed("U") != 0) {
        if (current_heart >= 0) {
            hearts[current_heart]->Break();
            current_heart -= 1 ;
        }
    }
}

void TakeDamage() {

}

void Player::OnCollision(Collision collision) {
    // Prevent falling
    if (collision.collision_side == BOTTOM && collision.this_dy > 0 && !is_jumping) {
        body->SetDY(0);
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

void Player::CreateHeart() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(50, 200);

    int scale = dist(gen);

    Heart* clone = new Heart(renderer, "Heart_clone", pos_x + (width / 2), pos_y, 2, scale, scale, 0, "/Users/admin/TelescopeEngine/media/images/Heart-1.png");

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
