#ifndef EDITOR_H
#define EDITOR_H

#include "../dependencies.h"
#include "../rendering/Renderer.h"

class Editor {
    public:
    Editor() {
        window = InitializeWindow(1440, 900);
        renderer = InitializeRenderer(window);
    }

    private:
    SDL_Window* window;
    SDL_Renderer* renderer;

};

#endif
