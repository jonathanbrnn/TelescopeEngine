#include "Spikes.h"

void Spikes::Start() {
    AddBody(1, true);
    AddCollider();
    AddAnimator();

    animator->AddState("idle", idle, 5);
    animator->AddState("walking", walking, 5);

    animator->SetState("idle");

    FlipTexture(FLIP_HORIZONTAL, true);
}

void Spikes::Update() {
    if (pos_x < 1000 || pos_x > 1350) {
        animator->SetState("idle");
        body->SetDX(0);
        played_idle = 5;
        is_idle = true;
        if (pos_x < 1000) {
            SetPosition(1001, pos_y);
        }
        else {
            SetPosition(1349, pos_y);
        }
    }

    if (animator->OnAnimationEnd() != 0 && is_idle) {
        played_idle -= 1;
    }

    if (is_idle && played_idle > 0) {
        is_idle = false;
        speed = speed * -1;
        FlipTexture(FLIP_HORIZONTAL, true);
        animator->SetState("walking");

    }

    if (!is_idle) {
        body->SetDX(speed);
    }
}

void Spikes::OnCollision(Collision collision) {
    if (collision.collision_side == BOTTOM && collision.this_dy > 0) {
        body->SetDY(0);
    }
}
