#include <SDL.h>
#include <vector>
#include "EntityManager.h"
#include "../input/InputManager.h"
#include "../rendering/Renderer.h"
#include "../entities/GameObject.h"

void Update(SDL_Renderer* renderer, map<int, vector<GameObject*>>& gameObjects); 