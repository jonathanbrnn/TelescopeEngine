#include "Animator.h"
#include "AnimationState.h"

Animator::Animator() {}

int Animator::UpdateAnimator() {
    if (current_state->UpdateState() != 0 && animate) {
        current_frame = current_state->GetCurrentFramePath();
        return 1;
    }

    return 0;
}

void Animator::AddState(string state_name, vector<string> frames, int frame_delay) {
    if (animation_states.find(state_name) != animation_states.end()) {
        cout << "ANIMATOR: an animation state with name: " << state_name << " already exists. Choose a different name." << endl;
    }
    else {
        AnimationState* new_animation_state = new AnimationState(frames, frame_delay);
        animation_states[state_name] = new_animation_state;
        animation_state_count += 1;
    }
}

void Animator::SetState(string state_name) {
    if (animation_states.find(state_name) != animation_states.end()) {
        // THIS IS NECCESSARY BECAUSE ELSE THE CONSOLE WILL BE AHHH
        if (state_name != current_state_name) {
            current_state = animation_states[state_name];
            current_state->StartState();
            current_state_name = state_name;
        }
    }
    else {
        cout << "ANIMATOR: an animation state with name: " << state_name << " could not be found!" << endl;
    }
}

void Animator::Play() {
    animate = true;
}

void Animator::PlayFrom(string state_name, int start_frame) {
    animate = true;
    current_state = animation_states[state_name];
    current_state->SetCurrentFrame(start_frame - 1);
}

void Animator::Stop() {
    animate = false;
}

int Animator::OnAnimationEnd() {
    if (current_state->GetCurrentFrame() == current_state->GetAnimationSize() - 1) {
        return 1;
    }

    return 0;
}

Animator::~Animator() {
    for (auto [animation_state_name, animation_state] : animation_states) {
        delete animation_state;
    }
}
