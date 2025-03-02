#ifndef RENDERER_H
#define RENDERER_H
#include <SDL.h>
#include <iostream>
#include <vector>
#include <map>
#include "../entities/GameObject.h"

using namespace std; 

SDL_Window* InitializeWindow(int screenWidth = 600, int screenHeight = 400, int windowPositionX = 0, int windowPositionY = 0, const string& windowTitle = "Telescope Engine");
SDL_Renderer* InitializeRenderer(SDL_Window* window);
void UpdateRenderer(SDL_Renderer* renderer, float deltaTime, const int fps = 60); 

#endif