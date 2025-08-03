#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <random>

#include "Cell.h"
#include "../entities/GameObject.h"
#include "../dependencies.h"

class Grid : public GameObject {
    public: 
    Grid(SDL_Renderer* renderer, string name, float pos_x = 0, float pos_y = 0, float pos_z = 0, float width = 1,
        float height = 1, float rotation = 0, string texture_filepath = "") : GameObject(renderer, name, pos_x, pos_y, pos_z, width, height, rotation, texture_filepath) {}
    
    void Start() override; 
    void Update() override; 

    Grid* Clone() const override { return new Grid(*this); }

    void SetCellThreshold(int cell_threshold); 

    private: 
    int screen_width; 
    int screen_height; 
    
    int cell_threshold; 
    bool cell_threshold_set = false; 

    int common_divisor = -1; 

    vector<vector<Cell*>> cells; 
    vector<vector<int>> cells_bin; 

    bool is_paused = false; 

    int frame_delay = 20; 
    int current_frame = 0; 
}; 

#endif