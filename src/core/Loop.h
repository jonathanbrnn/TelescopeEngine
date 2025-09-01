#ifndef LOOP_H
#define LOOP_H

#include "../dependencies.h"
#include "ManagerHub.h"

class Loop {
    public: 
    Loop() {} 
    // Updates all functionality and produces the next frame. 
    virtual void UpdateCore() = 0; 

    ManagerHub* managerHub = nullptr; 
    bool running = false; 
}; 

#endif 