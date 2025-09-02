#include "Renderer.h"

int Renderer::InitializeRenderer(const int screen_width, const int screen_height, const int window_pos_x, const int window_pos_y, const string window_title, const bool use_vsync, const bool fullscreen) {
    window = nullptr;  

    if (SDL_INIT_VIDEO < 0) {
        printf("SDL could not initilize! SDL_Error: %s\n", SDL_GetError());
    }
    else {
        if (fullscreen) {
            window = SDL_CreateWindow(window_title.c_str(), window_pos_x, window_pos_y, screen_width, screen_height, SDL_WINDOW_FULLSCREEN_DESKTOP);
            SDL_ShowWindow(window); 
        } 
        else {
            window = SDL_CreateWindow(window_title.c_str(), window_pos_x, window_pos_y, screen_width, screen_height, SDL_WINDOW_SHOWN);
        }

        if(!window) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
    }

    renderer = nullptr; 

    if (!window) {
        printf("Window was not created properly!");
    }
    else {
        if (use_vsync) { renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); }
        else { renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); }

        if (!renderer) {
            printf("Renderer could not not be created! SDL_Error: %s\n", SDL_GetError());
        }
    }

    managerHub = &ManagerHub::GetInstance(); 

    return 0; 
}

SDL_Renderer* Renderer::Get_Renderer() {
    if (renderer != nullptr) {
        return this->renderer; 
    }
    cout << "WARNING! NO RENDERER WAS RETURNED." << endl; 
    return nullptr; 
}

SDL_Window* Renderer::Get_Window() {
    if (window != nullptr) {
        return this->window; 
    }
    cout << "WARNING: NO WINDOW WAS RETURNED." << endl; 
    return nullptr; 
}