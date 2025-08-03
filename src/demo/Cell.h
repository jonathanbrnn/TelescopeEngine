#ifndef CELL_H
#define CELL_H

#include <iostream>

#include "../entities/GameObject.h"

class Cell : public GameObject {
    public: 
    Cell(SDL_Renderer* renderer, string name, float pos_x = 0, float pos_y = 0, float pos_z = 0, float width = 1, 
        float height = 1, float rotation = 0, string texture_filepath = "../media/images/cell_state0.png") : GameObject(renderer, name, pos_x, pos_y, pos_z, width, height, rotation, texture_filepath) {}
    
    int GetState() { return current_state; }
    void SetState(int new_state); 
    void FlipState(); 
    
    Cell* Clone() const override { return new Cell(*this); }

    private:  
    int current_state = 0; 
    vector<string> states = {"../media/images/cell_state0.png", "../media/images/cell_state1.png"}; 
}; 

#endif