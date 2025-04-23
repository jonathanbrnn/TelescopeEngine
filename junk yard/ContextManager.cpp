#include "ContextManager.h"

void ContextManager::SetWindow(SDL_Window* window) { this->window = window; }
SDL_Window* ContextManager::GetWindow() {
    if (window) {
        return window;
    }

    cout << "CONTEXTMANAGER: Window could not be returned because it was not properly initialized!" << endl;
    return nullptr;
}

void ContextManager::SetRenderer(SDL_Renderer* renderer) { this->renderer = renderer; }
SDL_Renderer* ContextManager::GetRenderer() {
    if (renderer) {
        return renderer;
    }

    cout << "CONTEXTMANAGER: Renderer could not be returned because it was not properly initialized!" << endl;
    return nullptr;
}

void ContextManager::SetGravityConstant(float gravity_constant)  { this->gravity_constant = gravity_constant; }
float ContextManager::GetGravityConstant() { return gravity_constant; }

void ContextManager::SetTargetFramerate(int target_framerate) {
    if (!is_running) {
        this->target_framerate = target_framerate;
    }
    else {
        cout << "CONTEXTMANAGER: Can not set target framerate during runtime!" << endl;
    }
}
int ContextManager::GetTargetFramerate() { return target_framerate; }

void ContextManager::SetVsync(bool use_vsync) { this->use_vsync = use_vsync; }
bool ContextManager::GetVsync() { return use_vsync; }

void ContextManager::OnStart() {
    is_running = true;
}
