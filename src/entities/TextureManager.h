#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <iostream>
#include <string>
#include <unordered_map>
#include "../dependencies.h"

using namespace std;

class TextureManager {
public:
    // Get the singleton instance of TextureManager
    static TextureManager& GetInstance();

    // Load a texture from a file, using the renderer. Returns the SDL_Texture pointer.
    SDL_Texture* LoadTexture(string filepath, SDL_Renderer*& renderer);

    // Cleanup all loaded textures
    void Cleanup();

private:
    // A map to store loaded textures with their file paths as keys
    unordered_map<string, SDL_Texture*> textures;

    // Private constructor for singleton pattern
    TextureManager();

    // Private destructor to ensure proper cleanup
    ~TextureManager();

    // Delete copy constructor and assignment operator to enforce singleton
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;
};

#endif // TEXTURE_MANAGER_H
