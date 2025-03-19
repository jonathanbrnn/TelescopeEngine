#ifndef ANIMATIONSTATE_H
#define ANIMATIONSTATE_H

#include <iostream>

using namespace std;

class AnimationState {
    public:
    AnimationState(vector<string> frames, int frame_delay);

    void StartState();

    int UpdateState();

    string GetCurrentFramePath();

    int GetCurrentFrame();

    void SetCurrentFrame(int frame);

    int GetAnimationSize();

    private:
    // The frame the animation is currently at (frames[current_frame]).
    int current_frame;

    // Frames passed during runtime since the last increase to current_frame.
    int frames_passed;

    // The amount of frames that pass during runtime before moving to the next frame of the animation.
    int frame_delay;

    // The filepaths to the individual animation frames.
    vector<string> frames;

    // The animations size (frames.size())
    int frames_size;
};

#endif
