#include "Telescope.h"

void Engine::Entry(vector<GameObject*> prefabs) {
    // ADD JSON CONFIG READOUT TO DETERMINE
    // EDITOR | GAME 
    // screen_width | screen_height 
    // window_pos_x | window_pos_y
    // window_title
    // full_screen 
    // VSYNC ON | OFF 
    // ... 

    Renderer* renderer = nullptr;

    if (mode == GAME) {
        renderer = &GameRenderer::GetInstance(); 
        loop = &GameLoop::GetInstance(); 
    }
    else {
        renderer = &EditorRenderer::GetInstance(); 
        loop = &EditorLoop::GetInstance(); 
    }
    
    renderer->InitializeRenderer(screen_width, screen_height, window_pos_x, window_pos_y, window_title, use_vsync);

    Camera* camera = new Camera(screen_width, screen_height);

    EntityManager* entityManager = &EntityManager::GetInstance();

    TimeManager* timeManager = &TimeManager::GetInstance();

    CollisionManager* collisionManager = &CollisionManager::GetInstance();

    TextureManager* textureManager = &TextureManager::GetInstance();

    InputManager* inputManager = &InputManager::GetInstance(); 

    ManagerHub* managerHub = &ManagerHub::GetInstance(); 

    managerHub->OnStart(renderer, camera, entityManager, timeManager, collisionManager, textureManager, inputManager);

    managerHub->SetStorage(screen_width, screen_height);

    this->managerHub = managerHub; 

    camera->StartCamera(managerHub);

    textureManager->OnStart(managerHub); 

    collisionManager->OnStart(managerHub);

    inputManager->OnStart(managerHub); 

    entityManager->OnStart(prefabs); 

    cout << "ENGINE: Entry complete." << endl; 
}

void Engine::Runtime() {
    loop->UpdateCore(); 
    cout << "ENGINE: Runtime complete." << endl; 
}

void Engine::Exit() {
    SDL_DestroyRenderer(managerHub->renderer->Get_Renderer()); 
    SDL_DestroyWindow(managerHub->renderer->Get_Window()); 
    SDL_Quit(); 
    cout << "ENGINE: Exit complete." << endl; 
}

Mode Engine::Get_Mode() { return mode; }