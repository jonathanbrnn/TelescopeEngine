#ifndef RUNTIME_h
#define RUNTIME_h

#include <SDL.h>
#include <vector>
#include "EntityManager.h"
#include "../input/InputManager.h"
#include "../rendering/Renderer.h"
#include "../entities/GameObject.h"

void Update(SDL_Renderer* renderer, EntityManager& entityManager); 
void MovePlayer(GameObject* player, KeyPress key); 

#endif