#ifndef AUDIOMANAGER_h
#define AUDIOMANAGER_h
#include <SDL.h>
#include <SDL2/SDL_audio.h>
#include <iostream>

using namespace std;

class AudioManager {
    public:
    explicit AudioManager();
    static AudioManager& GetInstance();

    private:
    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;


};

#endif
