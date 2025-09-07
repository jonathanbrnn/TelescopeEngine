#include "Telescope.h"

void Engine::Entry(vector<GameObject*> prefabs) {

    if (fs::exists(config_filepath)) {
        ifstream in_file(config_filepath); 
        nlohmann::json config_in;  
        in_file >> config_in; 
        in_file.close(); 

        if (config_in["mode"] == 0) {
            mode = GAME; 
        }
        else {
            mode = EDITOR; 
        }

        use_vsync = config_in["use_vsync"]; 
        fullscreen = config_in["fullscreen"]; 

        window_title = config_in["window_title"]; 

        screen_width = config_in["screen_dimensions"][0]; 
        screen_height = config_in["screen_dimensions"][1]; 

        window_pos_x = config_in["window_pos"][0]; 
        window_pos_y = config_in["window_pos"][1]; 

        if (mode == EDITOR) {
            bool boot_fullscreen = config_in["boot_editor_in_fullscreen"]; 
            fullscreen = boot_fullscreen; 
        }
    }
    else {
        cout << "ENGINE: WARNING! The config file could not be read. The engine was booted using default parameter." << endl; 
    }

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
    
    renderer->InitializeRenderer(screen_width, screen_height, window_pos_x, window_pos_y, window_title, use_vsync, fullscreen);

    Camera* camera = new Camera(screen_width, screen_height);

    EntityManager* entityManager = &EntityManager::GetInstance();

    TimeManager* timeManager = &TimeManager::GetInstance();

    CollisionManager* collisionManager = &CollisionManager::GetInstance();

    TextureManager* textureManager = &TextureManager::GetInstance();

    InputManager* inputManager = &InputManager::GetInstance(); 

    ManagerHub* managerHub = &ManagerHub::GetInstance(); 

    managerHub->OnStart(renderer, camera, entityManager, timeManager, collisionManager, textureManager, inputManager);

    managerHub->SetStorage(screen_width, screen_height); 

    camera->StartCamera(managerHub);

    textureManager->OnStart(managerHub); 

    collisionManager->OnStart(managerHub);

    inputManager->OnStart(managerHub); 

    entityManager->OnStart(prefabs); 

    this->managerHub = managerHub;

    cout << "ENGINE: Entry complete." << endl; 
}

void Engine::Runtime() {
    loop->UpdateCore(); 
    cout << "ENGINE: Runtime complete." << endl; 
}

void Engine::Exit() {
    if (mode == EDITOR) {
        ImGui_ImplSDLRenderer2_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

    SDL_DestroyRenderer(managerHub->renderer->Get_Renderer()); 
    SDL_DestroyWindow(managerHub->renderer->Get_Window()); 
    SDL_Quit(); 
    cout << "ENGINE: Exit complete." << endl; 
}

Mode Engine::Get_Mode() { return mode; }