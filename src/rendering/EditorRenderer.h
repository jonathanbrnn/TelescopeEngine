#ifndef EDITORRENDERER_H
#define EDITORRENDERER_H

#include "Renderer.h"
#include "../core/Editor.h"

#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer2.h"

class EditorRenderer : public Renderer {
    public: 
    static EditorRenderer& GetInstance() {
        static EditorRenderer instance; 
        return instance; 
    }

    int InitializeRenderer(const int screen_width = 1440, const int screen_height = 900, const int window_pos_x = 0, const int window_pos_y = 0, const string window_title = "TELESCOPEENGINE", const bool use_vsync = true, const bool fullscreen = false) override; 
    void UpdateRenderer() override; 

    private: 
    EditorRenderer() : Renderer() {}; 

    Editor* editor = nullptr; 

    EditorRenderer(const EditorRenderer&) = delete; 
    EditorRenderer& operator=(const EditorRenderer&) = delete; 
}; 

#endif