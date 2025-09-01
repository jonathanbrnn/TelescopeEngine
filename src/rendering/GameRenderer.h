#ifndef GAMERENDERER_H 
#define GAMERENDERER_H 

#include "Renderer.h"

class GameRenderer : public Renderer {
    public: 
    static GameRenderer& GetInstance() {
        static GameRenderer instance; 
        return instance; 
    }

    void UpdateRenderer() override;

    private: 
    GameRenderer() : Renderer() {} 

    GameRenderer(const GameRenderer&) = delete; 
    GameRenderer& operator=(const GameRenderer&) = delete; 
}; 

#endif 