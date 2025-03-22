#include "AudioManager.h"
#include <SDL.h>
#include <iostream>

using namespace std;

AudioManager& AudioManager::GetInstance() {
    static AudioManager instance;
    return instance;
}
