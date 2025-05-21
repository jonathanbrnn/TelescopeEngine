#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <iostream>
#include "AnimationState.h"
#include <map>

using namespace std;

class Animator {
    public:
    Animator();

    // Returns 0 if the current_frame wasn't changed, 1 if it was.
    int UpdateAnimator();

    // Adds a new state to this Animator.
    void AddState(string state_name, vector<string> frames, int frame_delay);

    // Will set the current animation state to the one specified.
    void SetState(string state_name);

    // Resumes playing the last animation after Stop().
    void Play();

    // Resumes playing a specified animation after Stop().
    // Pass the name of an animation state and/or a frame on which to start the animation at
    void PlayFrom(string state_name, int start_frame);

    // returns 1 upon the last frame of the current animation.
    int OnAnimationEnd();

    // Stops animating at the current frame.
    void Stop();

    string current_frame;
    int animation_state_count = 0;
    string current_state_name = "";

    Animator(const Animator& other);

    ~Animator();

    private:
    bool animate = true;
    AnimationState* current_state;
    map<string, AnimationState*> animation_states;
};

#endif
