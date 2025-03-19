#include "AnimationState.h"

AnimationState::AnimationState(vector<string> frames, int frame_delay) {
    this->frames = frames;
    this->frame_delay = frame_delay;

    current_frame = -1;
    frames_passed = 0;

    frames_size = frames.size();
}

void AnimationState::StartState() {
    current_frame = -1;
    frames_passed = 0;
}

int AnimationState::UpdateState() {
    frames_passed += 1;

    if (frames_passed % frame_delay == 0) {
        frames_passed = 0;
        current_frame += 1;

        if (current_frame >= frames_size) {
            current_frame = 0;
        }

        return 1;

    }

    return 0;
}

string AnimationState::GetCurrentFramePath() {
    return frames[current_frame];
}

int AnimationState::GetCurrentFrame() {
    return current_frame;
}

void AnimationState::SetCurrentFrame(int frame) {
    current_frame = frame;
}

int AnimationState::GetAnimationSize() {
    return frames_size;
}
