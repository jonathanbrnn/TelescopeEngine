#include "EditorRenderer.h"

int EditorRenderer::InitializeRenderer(const int screen_width, const int screen_height, const int window_pos_x, const int window_pos_y, const string window_title, const bool use_vsync, const bool fullscreen) {
    window = nullptr;  

    if (SDL_INIT_VIDEO < 0) {
        printf("SDL could not initilize! SDL_Error: %s\n", SDL_GetError());
    }
    else {
        if (fullscreen) {
            window = SDL_CreateWindow(window_title.c_str(), window_pos_x, window_pos_y, screen_width, screen_height, SDL_WINDOW_FULLSCREEN_DESKTOP);
            SDL_ShowWindow(window); 
        } 
        else {
            window = SDL_CreateWindow(window_title.c_str(), window_pos_x, window_pos_y, screen_width, screen_height, SDL_WINDOW_SHOWN);
        }

        if(!window) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
    }

    renderer = nullptr; 

    if (!window) {
        printf("Window was not created properly!");
    }
    else {
        if (use_vsync) { renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); }
        else { renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); }

        if (!renderer) {
            printf("Renderer could not not be created! SDL_Error: %s\n", SDL_GetError());
        }
    }

    IMGUI_CHECKVERSION(); 
    ImGui::CreateContext(); 
    ImGuiIO& io = ImGui::GetIO(); (void)io; 

    ImGui::StyleColorsClassic(); 

    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    editor = &Editor::GetInstance(); 
    managerHub = &ManagerHub::GetInstance(); 

    return 0; 
}

void EditorRenderer::UpdateRenderer() {
    float delta_time = managerHub->timeManager->GetDeltaTime(); 

    Camera* camera = managerHub->camera; 
    camera->UpdateCamera(delta_time); 

    SDL_RenderClear(renderer); 

    for (auto& [pos_z, game_objects] : managerHub->entityManager->visible_objects) {
        for (auto* game_object : game_objects) {
            SDL_Rect destination; 
            destination.x = static_cast<int>((game_object->pos_x - camera->x) * camera->zoom);
            destination.y = static_cast<int>((game_object->pos_y - camera->y) * camera->zoom);
            destination.w = static_cast<int>(game_object->width * game_object->scale_x * camera->zoom);
            destination.h = static_cast<int>(game_object->height * game_object->scale_y * camera->zoom);

            SDL_Point center;
            center.x = destination.w / 2;
            center.y = destination.h / 2;

            SDL_RendererFlip flip = SDL_FLIP_NONE;
            if (game_object->flip_texture) {
                if (game_object->flip_mode == FLIP_HORIZONTAL) {
                    flip = SDL_FLIP_HORIZONTAL;
                }
                else if (game_object->flip_mode == FLIP_VERTICAL) {
                    flip = SDL_FLIP_VERTICAL;
                }
            }

            SDL_RenderCopyEx(
                renderer,
                game_object->texture,
                nullptr,
                &destination,
                static_cast<double>(game_object->rotation),
                &center,
                flip
            );
 
        }
    }

    SDL_RenderPresent(renderer);
}