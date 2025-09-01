#ifndef EDITORLOOP_H
#define EDITORLOOP_H

#include "Loop.h"
#include "ManagerHub.h"

class EditorLoop : public Loop {
    public: 
    static EditorLoop& GetInstance() {
        static EditorLoop instance; 
        return instance; 
    }

    void UpdateCore() override; 

    private: 
    EditorLoop() : Loop() {} 

    EditorLoop(const EditorLoop&) = delete; 
    EditorLoop& operator=(const EditorLoop&) = delete; 
}; 

#endif 