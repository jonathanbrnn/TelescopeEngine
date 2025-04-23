#ifndef CONTEXTMANAGER_H
#define CONTEXTMANAGER_H

#include "SDL2/SDL_render.h"
#include "SDL2/SDL_video.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <string>


using namespace std;

// The context manager stores global constant variables (f.e.: renderer, gravityconstant).
class ContextManager {
    public:
    ContextManager(const ContextManager&) = delete;
    ContextManager& operator=(const ContextManager&) = delete;

    static ContextManager& GetInstance() {
        static ContextManager instance;
        return instance;
    }


    void SetWindow(SDL_Window* window);
    SDL_Window* GetWindow();

    void SetRenderer(SDL_Renderer* renderer);
    SDL_Renderer* GetRenderer();

    void SetGravityConstant(float gravity_constant);
    float GetGravityConstant();

    void SetTargetFramerate(int target_framerate);

    int GetTargetFramerate();

    void SetVsync(bool use_vsync);
    bool GetVsync();

    void OnStart();

    private:
    bool is_running = false;

    float gravity_constant = 1;

    int target_framerate = 120;

    bool use_vsync = true;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    explicit ContextManager() {}
};

#endif
