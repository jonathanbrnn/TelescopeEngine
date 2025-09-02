#ifndef RENDERER_H 
#define RENDERER_H

#include <SDL.h>
#include <SDL_render.h>
#include <SDL_image.h>
#include <SDL_audio.h>

#include "../core/ManagerHub.h"

#include <iostream>

using namespace std; 

class Renderer {
    public: 
    int InitializeRenderer(const int screen_width = 1440, const int screen_height = 900, const int window_pos_x = 0, const int window_pos_y = 0, const string window_title = "TELESCOPEENGINE", const bool use_vsync = true, const bool fullscreen = false); 

    virtual void UpdateRenderer() = 0; 
    
    SDL_Renderer* Get_Renderer(); 

    SDL_Window* Get_Window(); 
 
    SDL_Window* window = nullptr; 
    SDL_Renderer* renderer = nullptr; 

    ManagerHub* managerHub = nullptr; 

    Renderer() {}

    ~Renderer() {} 
    
    Renderer(const Renderer&) = delete; 
    Renderer& operator=(const Renderer&) = delete; 
};

#endif