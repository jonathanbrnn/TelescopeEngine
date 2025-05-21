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

    Walk();
    Jump();

    InputManager* inp = managerHub->inputManager;

    if (inp->IsPressed("Down")) {
        SetScale(this->scale_x - 0.1, this->scale_y - 0.1);
    }
    if (inp->IsPressed("Up")) {
        SetScale(this->scale_x + 0.1, this->scale_y + 0.1);
    }

    if(inp->IsPressed("F")) {
        managerHub->camera->ToggleSmoothFollow(1, "Jonathan");
    }
    if(inp->IsPressed("G")) {
        managerHub->camera->ToggleSmoothFollow(1.4, "Spikes");
    }
    if(inp->IsPressed("J")) {
        managerHub->camera->ToggleSmoothFollow(3, "Heart1");
    }

    if(inp->IsPressed("L")) {
        SetPosition(10, -100);
    }

    if(inp->IsPressed("+")) {
        rotation += 5.0f;
    }

    if(managerHub->inputManager->IsPressed("C")) {
        managerHub->entityManager->Instantiate("Jonathan", 0, 0);
    }

    if (managerHub->inputManager->IsPressed("H") != 0) {
        CreateHeart();
    }

    if(inp->IsPressed("K")) {
        managerHub->entityManager->Instantiate("ground_left", pos_x, pos_y, 100, 0, -1);
    }

    if (pos_y > 1100) {
        TakeDamage();
    }
}

void Player::TakeDamage() {
    if (current_heart >= 0) {
        hearts[current_heart]->Break();
        current_heart -= 1 ;
        ResetPosition();
    }
    else {
        managerHub->entityManager->Delete(name);
    }
}

void Player::Walk() {
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
}

void Player::OnCollision(Collision collision) {
    // Prevent falling
    if (collision.collision_side == BOTTOM && collision.this_dy > 0) {
        body->SetDY(0);
    }

    if (collision.contact_name == "Spikes") {
        TakeDamage();
    }

    is_grounded = collision.collision_side == BOTTOM;
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
    /*
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(50, 200);

    int scale = dist(gen);

    Heart* clone = new Heart(renderer, "Heart_clone", pos_x + (width / 2), pos_y, 2, scale, scale, 0, "/Users/admin/TelescopeEngine/media/images/Heart-1.png");

    managerHub->entityManager->AddNewObject(clone);
    */

    managerHub->entityManager->Instantiate("Heart1", pos_x, pos_y, 100, 0, -1);
}

void Player::ResetPosition() {
    SetPosition(100, 100);
}

void Player::Jump() {
    if (is_grounded) { jumps = 2; }

    if (managerHub->inputManager->IsPressed("Space") != 0 && jumps > 0) {

        if (jumps == 1) {
            // MAKE IT POSSIBLE TO DELETE A FORCE FROM THE BODY.
            // F.E.: Double jump, left over dy force is carried over to the second jump, making it a bit stronger than the first.
            //body->forces.clear();
        }

        jumps -= 1;
        body->ApplyForce(-10, 1, LINEAR, AXIS_Y);
        is_grounded = false;

        cout << jumps << endl;
    }
}
