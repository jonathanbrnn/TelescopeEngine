#ifndef EDITORLOOP_H
#define EDITORLOOP_H

#include "Loop.h"
#include "Editor.h"

#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer2.h"

class EditorLoop : public Loop {
    public: 
    static EditorLoop& GetInstance() {
        static EditorLoop instance; 
        return instance; 
    }

    void UpdateCore() override; 

    private: 
    EditorLoop() : Loop() {} 

    Editor* editor = nullptr; 

    EditorLoop(const EditorLoop&) = delete; 
    EditorLoop& operator=(const EditorLoop&) = delete; 
}; 

#endif 