#include "Celestine.h"

void Celestine::Whisper(int code) {
    switch (code)
    {
    case 1:
        current_image += 1; 
       
        if (current_image >= us.size()) {
            current_image = 0; 
        }

        texture = TextureManager::GetInstance().LoadTexture(us[current_image], renderer);

        break;
    
    default:
        break;
    }
}