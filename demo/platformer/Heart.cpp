#include "Heart.h"

void Heart::Start() {
    AddBody(1, false);
    AddAnimator();
    animator->AddState("default", default_anim, 5);
    animator->AddState("break", breaking_anim, 5);
    animator->SetState("default");  
}

void Heart::Update() {
    if (is_broken && animator->OnAnimationEnd() != 0) {
        managerHub->entityManager->Delete(name);
    }
}

void Heart::Break() {
    is_broken = true;
    animator->SetState("break");
}

void Heart::OnCollision(Collision collision) {}
