#ifndef RUNTIME_h
#define RUNTIME_h

#include <SDL.h>
#include <vector>
#include "ManagerHub.h"
#include "../input/InputManager.h"
#include "../rendering/Renderer.h"
#include "../entities/GameObject.h"

void UpdateAll(SDL_Renderer* renderer);

#endif
