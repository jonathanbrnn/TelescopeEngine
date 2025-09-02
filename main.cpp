#include "src/Telescope.h"
#include "demo/platformer/Heart.h"

int main() {
    Engine* Engine = &Engine::GetInstance(); 

    vector<GameObject*> prefabs; 

    // GAMEOBJECTS: 

    Heart* heart = new Heart("heart", 100, 100, 0, 100, 100); 
    prefabs.push_back(heart); 

    // ...

    Engine->Entry(prefabs); 
    Engine->Runtime(); 
    Engine->Exit();

    return 0; 
}