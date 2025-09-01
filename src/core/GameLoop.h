#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "Loop.h"

class GameLoop : public Loop {
    public: 
    static GameLoop& GetInstance() {
        static GameLoop instance; 
        return instance; 
    }

    void UpdateCore() override; 

    private: 
    GameLoop() : Loop() {} 

    GameLoop(const GameLoop&) = delete; 
    GameLoop& operator=(const GameLoop&) = delete; 
};

#endif