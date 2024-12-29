#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>
#include "TextureManager.h"

using namespace std; 

/*
class TextureManager {
    public: 
    static TextureManager& GetInstance() {
        static TextureManager instance; 
        return instance; 
    }

    SDL_Texture* LoadTexture(const string filepath, SDL_Renderer*& renderer) {
        if (textures.find(filepath) == textures.end()) {
            SDL_Texture* texture = IMG_LoadTexture(renderer, filepath.c_str()); 

            if (!texture) {
                printf("Could not load image! %s\n", SDL_GetError()); 
            }

            textures[filepath] = texture; 
        }

        return textures[filepath]; 
    }

    void Cleanup() {
        for(auto& pair : textures) {
            SDL_DestroyTexture(pair.second); 
        }
        textures.clear(); 
    }

    private: 
    unordered_map<string, SDL_Texture*> textures; 
    TextureManager() {}
    ~TextureManager() {
        Cleanup(); 
    }
}; 
*/

TextureManager& TextureManager::GetInstance() {
    static TextureManager instance; 
    return instance; 
}

SDL_Texture* TextureManager::LoadTexture(string filepath, SDL_Renderer*& renderer) {
    if (textures.find(filepath) == textures.end()) {
        SDL_Texture* texture = IMG_LoadTexture(renderer, filepath.c_str()); 

        if (!texture) {
            printf("TEXTUREMANAGER: Could not load texture! %s\n", SDL_GetError());
        }

        textures[filepath] = texture; 
    }

    return textures[filepath]; 
}

TextureManager::TextureManager() {}

TextureManager::~TextureManager() {
    Cleanup();
}

void TextureManager::Cleanup() {
    for (auto& pair : textures) {
        SDL_DestroyTexture(pair.second);
    }
    textures.clear(); 
}

