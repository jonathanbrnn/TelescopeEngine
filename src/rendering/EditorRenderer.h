#ifndef EDITORRENDERER_H
#define EDITORRENDERER_H

#include "Renderer.h"

class EditorRenderer : public Renderer {
    public: 
    static EditorRenderer& GetInstance() {
        static EditorRenderer instance; 
        return instance; 
    }

    void UpdateRenderer() override; 

    private: 
    EditorRenderer() : Renderer() {}; 

    EditorRenderer(const EditorRenderer&) = delete; 
    EditorRenderer& operator=(const EditorRenderer&) = delete; 
}; 

#endif