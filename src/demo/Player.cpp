#include "Player.h"

void Player::Start() {
    AddBody(1, false);
    AddCollider();
}

void Player::Update() {
    
}

void Player::OnCollision(Collision collision) {

}