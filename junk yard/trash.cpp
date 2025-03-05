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

/*
void GameObject::UpdateVelocity() {
    this->rect.x += this->dx; 
    this->rect.y += this->dy; 
}
*/

//posX, etc. are redundant since all the positional data is stored in rect anyway!

/* DEPRECATED -> Moved to constructor!
void GameObject::InitializeGameObject(SDL_Renderer* renderer, float posX, float posY, float posZ, 
                                       float scaleX, float scaleY, float rotation, const string& texture_filepath) {
    // Set transform parameters of this instance
    this->posX = posX;
    this->posY = posY;
    this->scaleX = scaleX;
    this->scaleY = scaleY;
    this->rotation = rotation;

    // Set the rectangle for rendering
    this->rect.x = static_cast<int>(posX);
    this->rect.y = static_cast<int>(posY);
    this->rect.w = static_cast<int>(scaleX);
    this->rect.h = static_cast<int>(scaleY);

    // Set texture of this instance
    this->texture = TextureManager::GetInstance().LoadTexture(texture_filepath, renderer);
    if (!texture) {
        printf("GAMEOBJECT: Could not load associated texture! SDL_Error: %s\n", SDL_GetError());
    }
}; 

OLD GAME OBJECT CLASS: 
class GameObject {
public:
    string name; 
    float pos_x, pos_y, pos_z;
    float w, h;
    float rotation;

    //Filepath to image
    string texture_filepath; 

    //Velocity
    //dx, dy: updated every frame with all active forces, responsible for changing the game object's position every frame. 
    float dx, dy; 
    float base_dx, base_dy; 

    SDL_Texture* texture;
    SDL_Rect rect;

    //Collisions 
    Collider collider; 
    bool hasBody; 
    
    // dynamic forces
    vector<Force> forces; 

    // VELOCITY - Set and update velocity and corresponding forces:

    void SetVelocity(float dx = 1, float dy = 1);
    void UpdateVelocity(float deltaTime);
    void ApplyForce(float initialForce, float duration, ForceMode updateMode, ForceAxis axis = AXIS_BOTH); 


    // Set and Update position directly (.posX, .posY)

    void UpdatePosition(float deltaTime); 
    void SetPosition(float x, float y); 

    //Constructor
    GameObject(SDL_Renderer* renderer, string name, float pos_x = 0.0f, float pos_y = 0.0f, float pos_z = 0.0f, 
                float width = 100.0f, float height = 100.0f, float rotation = 0.0f, 
                string texture_filepath = "/Users/jonathan/TelescopeEngine/media/sample_640×426.bmp", bool hasBody = true); 
};
*/

#include "GameObject.h"
#include "TextureManager.h"
#include <SDL_image.h>

#include <stdio.h>
#include <unistd.h>

#include <tuple>

using namespace std;

Collider::Collider(tuple<float, float> a, tuple<float, float> b, tuple<float, float> c, tuple<float, float> d) 
    : a(a), b(b), c(c), d(d) {} 

void Collider::OnCollision(Collision collison) {}

Force::Force(float force, float duration, ForceMode updateMode, ForceAxis axis) 
    : initial_force(force), duration(duration), update_mode(updateMode), axis(axis) {}

void Force::UpdateForce(float deltaTime) {
    last_frame_force = current_force;

    elapsed_time += deltaTime;
    elapsed_time = min(elapsed_time, duration);

    switch (update_mode) {
        case LINEAR:
            current_force = initial_force * (1 - (elapsed_time / duration)); 
            break;

        case QUADRATIC_EASE_IN: 
            current_force = initial_force * pow(elapsed_time / duration, 2); 
            break; 

        case QUADRATIC_EASE_OUT: 
            current_force = initial_force * (1 - pow(elapsed_time / duration, 2));  
            break;

        default:
            current_force = 0.0f; 
            break;
    }

    if (elapsed_time >= duration) {
        current_force = 0.0f;
    }
}

//void Collider::OnCollisionExit() {}

GameObject::GameObject(SDL_Renderer* renderer, string name, float pos_x, float pos_y, float pos_z, float width, float height, float rotation, string texture_filepath) {
    this->name = name; 
    
    this->pos_x = pos_x; 
    this->pos_y = pos_y; 
    this->pos_z = pos_z;

    this->width = width; 
    this->height = height; 
    
    this->rotation = rotation;
    
    // Set SDL_Rect's parameters
    rect.x = static_cast<int>(pos_x);
    rect.y = static_cast<int>(pos_y);
    rect.w = static_cast<int>(width);
    rect.h = static_cast<int>(height);
    
    // Set texture of this instance
    texture = TextureManager::GetInstance().LoadTexture(texture_filepath, renderer);
    if (!texture) {
        printf("GAMEOBJECT: Could not load associated texture! SDL_Error: %s\n", SDL_GetError());
    }
}

// VELOCITY - Set and update velocity and corresponding forces:

void GameObject::SetVelocity(float dx, float dy) {
    this->dx = dx; 
    this->dy = dy; 
    base_dx = dx; 
    base_dy = dy;
}

// currently a force is applied to both .dx and .dy equally  
void GameObject::UpdateVelocity(float deltaTime) {
    // Reset the velocity to avoid accumulating force over time.
    dx = base_dx; 
    dy = base_dy;

    // Stores the indices of all forces that have exceeded their duration. 
    vector<int> to_delete;

    // Update dx and dy with all currently active forces
    for (int i = 0; i < forces.size(); i++) {
        forces[i].UpdateForce(deltaTime);
        if (forces[i].elapsed_time <= forces[i].duration) {
            if (forces[i].axis == AXIS_X || forces[i].axis == AXIS_BOTH) {
                dx += forces[i].currentForce; 
            }
            if (forces[i].axis == AXIS_Y || forces[i].axis == AXIS_BOTH) {
                dy += forces[i].currentForce;
            }
        } else {
            cout << "DELETING: " << i << endl;
            toDelete.push_back(i);
        }
    }

    // Delete all expired forces 
    for (int i = toDelete.size() - 1; i >= 0; i--) {
        forces.erase(forces.begin() + toDelete[i]);
    }

    toDelete.clear();
    cout << forces.size() << endl;
}

void GameObject::ApplyForce(float initialForce, float duration, ForceMode updateMode, ForceAxis axis) {
    forces.emplace_back(initialForce, duration, updateMode, axis);
}

// Function to move the gameobject. Can only be used from Update() in RUNTIME, since it uses deltaTime. 
void GameObject::UpdatePosition(float deltaTime) {
    rect.x += dx * deltaTime * 100; 
    rect.y += dy * deltaTime * 100; 
    posX = rect.x;
    posY = rect.y;
    collider.a = {posX, posY};
    collider.b = {posX, posY + h};
    collider.c = {posX + w, posY + h};
    collider.d = {posX + w, posY};
}

// Function to set the position of the gameobject.
void GameObject::SetPosition(float x, float y) {
    rect.x = static_cast<int>(x);
    rect.y = static_cast<int>(y);
    posX = x;
    posY = y;
    collider.a = {posX, posY};
    collider.b = {posX, posY + h};
    collider.c = {posX + w, posY + h};
    collider.d = {posX + w, posY};
}


// ENTITYMANAGER (DEPRICATED)
//Creates a clone of an existing game object. Can be used during runtime. 
void EntityManager::Instantiate(string original_name, float posX, float posY, float posZ, float dx, float dy) {
    GameObject* gm = new GameObject(renderer, original_name, posX, posY, posZ, 
                                this->gameObjects[original_name]->w, this->gameObjects[original_name]->h, 
                                this->gameObjects[original_name]->rotation, this->gameObjects[original_name]->texture_filepath, this->gameObjects[original_name]->hasBody); 

    gm->SetVelocity(dx, dy); 
    this->active_gameObjects[gm->posZ].push_back(gm); 

    if (gm->hasBody) {
        this->collision_objects.push_back(gm); 
    }
}

void EntityManager::OnEnd() {
    for (auto& [name, gm]: this->gameObjects) {
        delete gm; 
    }
    this->gameObjects.clear(); 

    for (auto& [posZ, gameObjects]: this->active_gameObjects) {
        for (int i = 0; i < gameObjects.size(); i++) {
            delete gameObjects[i]; 
        }
    }
    this->active_gameObjects.clear(); 

    for (int i = 0; i < this->collision_objects.size(); i++) {
        delete this->collision_objects[i]; 
    }
    this->collision_objects.clear(); 
}

// Just to make sure I got everything from GameObject.cpp: 

// COLLIDER: 

Collider::Collider(tuple<float, float> a, tuple<float, float> b, tuple<float, float> c, tuple<float, float> d) {
    this->a = a; 
    this->b = b; 
    this->c = c; 
    this->d = d; 
}

void Collider::OnCollision(Collision collision) {}

// COLLISION: 

Collision::Collision(string contact_name, float contact_dx, float contact_dy, float this_dx, float this_dy, tuple<int, int> collision_point) {
    this->colli
}

// BODY: 

Body::Body(float mass, bool use_gravity) {
    this->mass = mass; 
    this->use_gravity = use_gravity;
    
    if (this->use_gravity) {
        // gravity_force = mass * storage.gravity_constant; 
    }
}

void Body::SetVelocity(float dx, float dy) {
    if (dx != NULL) {
        base_dx = dx; 
        this->dx = dy; 
    }
    if (dy != NULL) {
        base_dy = dy; 
        this->dy = dy; 
    }
}

void Body::UpdateVelocity(float delta_time) {
    dx = base_dx; 
    dy = base_dy; 

    for (auto force : forces) {
        force.UpdateForce(delta_time);

        if (force.axis == AXIS_X || force.axis == AXIS_BOTH) {
            dx += force.current_force; 
        }
        if (force.axis == AXIS_Y || force.axis == AXIS_BOTH) {
            dy += force.current_force; 
        }
    }

    if (use_gravity) {
        dy += gravity_force;
    }
}

void Body::ApplyForce(float initial_force, float duration, ForceMode update_mode, ForceAxis axis) {
    forces.emplace_back(initial_force, duration, update_mode, axis); 
}

// FORCE: 

Force::Force(float initial_force, float duration, ForceMode update_mode, ForceAxis axis) {
    this->initial_force = initial_force; 
    
    this->duration = duration; 

    this->update_mode = update_mode; 
    this->axis = axis; 
}

// THE OLD PLAYER MOVE LOGIC USED IN RUNTIME FOR TESTING PURPOSES: 

void MovePlayer(GameObject* player, KeyPress key) { 
    switch(key) {
        case KEY_PRESS_LEFT: 
            player->body->base_dx = -3; 
            break; 
        case KEY_PRESS_RIGHT: 
            player->body->base_dx = 3; 
            break; 
        case KEY_PRESS_UP: 
            player->body->base_dy = -3; 
            break; 
        case KEY_PRESS_DOWN: 
            player->body->base_dy = 3; 
            break; 
        case KEY_PRESS_SPACE: 
            player->Whisper(1);
            break; 
        case KEY_PRESS_ONE: 
            player->Whisper(2);
        case KEY_PRESS_TWO:
            break;
        case KEY_PRESS_THREE: 
            EntityManager::GetInstance().FindGameObjectByName("Celestine")->Whisper(1);
        default: 
            player->body->base_dx = 0; 
            player->body->base_dy = 0;
            break; 
    }    
}