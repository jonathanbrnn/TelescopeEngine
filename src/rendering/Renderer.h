#ifndef RENDERER_H
#define RENDERER_H
#include <iostream>
#include <vector>
#include <map>
#include "../dependencies.h"
#include "../entities/GameObject.h"
#include "../core/ManagerHub.h"
#include <SDL_render.h>

using namespace std;

SDL_Window* InitializeWindow(int screenWidth = 600, int screenHeight = 400, int windowPositionX = 0, int windowPositionY = 0, const string& windowTitle = "Telescope Engine");
SDL_Renderer* InitializeRenderer(SDL_Window* window, bool use_vsync = true);
void UpdateRenderer(SDL_Renderer* renderer);

#endif
