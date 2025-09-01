#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <iostream>
#include <string>
#include <unordered_map>
#include "../dependencies.h"
#include "../core/ManagerHub.h"
#include <filesystem>
namespace fs = std::filesystem;

using namespace std;

class TextureManager {
public:
    // Get the singleton instance of TextureManager
    static TextureManager& GetInstance();

    void OnStart(ManagerHub* managerHub); 

    // Load a texture from a file, using the renderer. Returns the SDL_Texture pointer.
    SDL_Texture* LoadTexture(string filepath);

    // Cleanup all loaded textures
    void Cleanup();

    ~TextureManager();

private:
    // ... 
    ManagerHub* managerHub = nullptr; 

    // A map to store loaded textures with their file paths as keys
    unordered_map<string, SDL_Texture*> textures;

    // ... 
    SDL_Renderer* renderer = nullptr; 

    // Private constructor for singleton pattern
    TextureManager();

    // Delete copy constructor and assignment operator to enforce singleton
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;
};

#endif // TEXTURE_MANAGER_H
