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

void TextureManager::OnStart(ManagerHub* managerHub) {
    cout << "is this being called?" << endl; 
    this->managerHub = managerHub; 
    if (managerHub->renderer != nullptr) {
        this->renderer = managerHub->renderer->Get_Renderer(); 
    }
    else {
        cout << "TEXTUREMANAGER: Failed to initialize properly and is missing access to the renderer." << endl;
    }
}

// DAS HIER IST DER WIRT WEIL ES NICHT ÜBERPRÜFT OB ES DEN FILEPATH ÜBERHAUPT GIBT SONDERN EINFACH VERSUCHT ZU LADEN
// improvement would be to just specify a folder for each objects animation which stores the frames. (?) 
SDL_Texture* TextureManager::LoadTexture(string filepath) {
    if (textures.find(filepath) == textures.end()) {
        if (!fs::exists(filepath)) {
            cout << "WARNING: No media found at filepath: " << filepath << ". Filepath was replaced with the default texture!" << endl; 
            filepath = "/Users/jonathan/TelescopeEngine/media/default/default_grid.png"; 
        }

        cout << filepath << endl; 

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

