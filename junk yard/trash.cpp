/*
int t = 1234; 
int *t_pointer = &t; 

char output(char a) {
    return a; 
}

void test() {
    int a = 5;
    float b = 4.5;
    int input; 
    std::cout << "TelescopeEngine by Jonathan" << std::endl; 
    std::cout << *t_pointer << std::endl;
    t = 1; 
    std::cout << t << std::endl; 
}

int main() {
    test();
    return 0;
} 

class Test {
    public: 
    void print(string a) 
    {
        std::cout << a << std::endl; 
    }
};

int main() {
    vector<string> test_vec{"Jonathan", "ist", "am", "ackern!"}; 

    for(int i = 0; i < test_vec.size(); i++)
    {
        std::cout << test_vec[i] << std::endl; 
    }

    Test t1; 
    Test t2; 
    
    string message = "Hallo Celestine"; 

    t1.print(message); 
    t2.print(message); 

    return 0;
}

*/



// OLD CODE THAT SUPPORTED MORE THAN ONE WINDOW BELOW. WAS SCRAPPED BECAUSE I CAN'T BE BOTHERED. 

/*
#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

using namespace std;

SDL_Window* createWindow(int screenWidth = 680, int screenHeight = 480, int windowPositionX = 0, int windowPositionY = 0, vector<int> screenSurfaceColor = {0, 0, 0}) {
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    } else {
        window = SDL_CreateWindow("TelescopeEngine", windowPositionX, windowPositionY, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
        if (!window) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        } else {
            screenSurface = SDL_GetWindowSurface(window);
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, screenSurfaceColor[0], screenSurfaceColor[1], screenSurfaceColor[2]));
            SDL_UpdateWindowSurface(window);
        }
    }

    return window;
}

void loadImage(SDL_Window* window, const string& filepath) {
    SDL_Surface* surface = SDL_GetWindowSurface(window); 
    SDL_Surface* imageSurface = IMG_Load(filepath.c_str()); 

    if (!imageSurface) {
        printf("Could not load image! %s\n", IMG_GetError());
        return;  
    }
    else {
        SDL_BlitSurface(imageSurface, NULL, surface, NULL); 

        SDL_UpdateWindowSurface(window);

        SDL_FreeSurface(imageSurface);  
    }
}

void closeEngine(vector<SDL_Window*>& windows) {
    for (SDL_Window* window : windows) {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
}

void runtime(vector<SDL_Window*>& windows, int fps = 60) {
    SDL_Renderer* renderer = SDL_CreateRenderer(windows[0], -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        printf("Renderer could not be initialized! SDL_Error: %s\n", SDL_GetError()); 
    }

    const int frameDelay = 1000 / fps;

    SDL_Event event;
    bool quit = false;

    

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {quit = true;}
            else if (event.type = SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE) {
                for (size_t i = 0; i < windows.size(); i++) {
                    if (SDL_GetWindowID(windows[i]) == event.window.windowID) {
                        SDL_DestroyWindow(windows[i]); 
                        windows.erase(windows.begin() + i); 
                        break; 
                    }
                }
            }
        }

        if (windows.empty()) {quit=true;}

        for (SDL_Window* window : windows) {
            SDL_UpdateWindowSurface(window);
        }

        SDL_Delay(frameDelay);
    }

    closeEngine(windows);
}

int main(int argc, char* args[]) {
    SDL_Window* window1 = createWindow(640, 426);
    vector<SDL_Window*> windows{window1};

    loadImage(windows[0], "media/sample_640×426.bmp"); 
    runtime(windows);

    return 0;
}
*/