#include "Heart.h"

void Heart::Start() {
    AddBody(1, false); 
    body->ApplyForce(-2, 3, QUADRATIC_EASE_IN, AXIS_Y);
}

void Heart::Update() {
    frame_delay += 1; 

    if (frame_delay % 5 == 0) {
        Animate(); 
        frame_delay = 0; 
    }
}

void Heart::OnCollision(Collision collision) {}

void Heart::Animate() {
    current_frame += 1; 

    if (current_frame >= frames.size()) {
        current_frame = 0; 
    }

    texture = managerHub->textureManager->LoadTexture(frames[current_frame], renderer);
}