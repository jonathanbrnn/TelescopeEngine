#ifndef EDITOR_H 
#define EDITOR_H 

#include "../dependencies.h"

#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer2.h"

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace std; 

class Editor {
    public: 
    static Editor& GetInstance() {
        static Editor instance; 
        return instance; 
    }

    void DrawUI(); 

    // Load and store entities

    private: 
    Editor() {}
    ~Editor() {}

    Editor(const Editor&) = delete; 
    Editor& operator=(const Editor&) = delete; 
}; 

#endif