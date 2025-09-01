#ifndef CELESTINE_H
#define CELESTINE_H 

#include "../entities/GameObject.h"

class Celestine : public GameObject {
    public: 
    Celestine(SDL_Renderer* renderer, string name, float pos_x = 0, float pos_y = 0, float pos_z = 0, float width = 1, 
        float height = 1, float rotation = 0, string texture_filepath = "../media/sample_640×426.bmp") : GameObject(renderer, name, pos_x, pos_y, pos_z, width, height, rotation, texture_filepath) {}
    
        void Whisper(int code) override; 

    private: 
    int current_image = 0; 
    vector<string> us = {"../media/images/Celestine.JPG", "../media/images/Celestine1.JPG", "../media/images/Celestine2.JPG"};  
};

#endif