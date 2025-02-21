#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "core/ManagerHub.h"
#include "core/EntityManager.h"
#include "core/TimeManager.h"
#include "core/Runtime.h"
#include "entities/GameObject.h"
#include "entities/CollisionManager.h"
#include <vector>
#include <map>


void InitializeEngine(SDL_Window*& window, SDL_Renderer*& renderer) {
    window = InitializeWindow(1000, 1000); 
    renderer = InitializeRenderer(window); 

    EntityManager::GetInstance(renderer); 
    
    TimeManager::GetInstance(); 

    CollisionManager::GetInstance(); 

    ManagerHub::GetInstance();
}

void closeEngine(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main() {
    SDL_Window* window = NULL; 
    SDL_Renderer* renderer = NULL; 

    ManagerHub& managerHub = ManagerHub::GetInstance(); 

    InitializeEngine(window, renderer);  

    GameObject gm1(renderer, "Player", 500.0f, 500.0f, 0.0f, 472 / 4, 268 / 4, 0, "../media/D5A7C13D-BA69-41D6-9BD7-B1DD66045837_4_5005_c Background Removed.png"); 
    GameObject gm2(renderer, "Enemy", 500.0f, 300.0f, -5.0f, 10.0f, 10.0f, 0.0f, "../media/sample_640×426.bmp"); 

    gm1.AddCollider(); 
    gm2.AddBody(1, false);
    gm2.AddCollider(); 

    vector<GameObject*> gameObjects; 

    gameObjects.push_back(&gm1); 
    gameObjects.push_back(&gm2);   

    managerHub.entityManager->OnStart(gameObjects);

    Update(renderer); 

    closeEngine(window, renderer); 

    return 0;
}