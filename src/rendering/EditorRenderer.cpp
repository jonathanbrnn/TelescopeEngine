#include "EditorRenderer.h"

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

            SDL_RenderPresent(renderer); 
        }
    }
}