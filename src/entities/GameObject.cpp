#include "GameObject.h"

using namespace std;

GameObject::GameObject(SDL_Renderer* renderer, string name, float pos_x, float pos_y, float pos_z, float width, float height, float rotation, string texture_filepath) {
    this->name = name;

    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->pos_z = pos_z;

    this->width = width;
    this->height = height;

    this->scale_x = 1;
    this->scale_y = 1;

    this->rotation = rotation;

    this->texture_filepath = texture_filepath;

    this->renderer = renderer;

    managerHub = &ManagerHub::GetInstance();

    // Set SDL_Rect's parameters
    rect.x = static_cast<int>(pos_x);
    rect.y = static_cast<int>(pos_y);
    rect.w = static_cast<int>(width);
    rect.h = static_cast<int>(height);

    collider = nullptr;

    body = nullptr;

    animator = nullptr;

    if (texture_filepath != "") {
        // Set texture of this instance
        texture = managerHub->textureManager->LoadTexture(texture_filepath, renderer);
        if (!texture) {
            printf("GAMEOBJECT: Could not load associated texture! SDL_Error: %s\n", SDL_GetError());
        }
    }
    else {
        texture = nullptr;
    }
}

void GameObject::CheckGameObject() {
    if (animator != nullptr && animator->animation_state_count == 0) {
        cout << "GAMEOBJECT: " << name << " has an animator attached to it but no animation states set." << endl;
        cout << "Use animator->AddState(...) in this objects Start() method to add at least one state." << endl;
    }
}

void GameObject::UpdateGameObject() {
    this->Update();
    float delta_time = managerHub->timeManager->GetDeltaTime();

    if (body != nullptr) {
        body->UpdateVelocity(delta_time);
    }

    UpdatePosition(delta_time);

    float current_width = width * scale_x;
    float current_height = height * scale_y;

    rect.w = static_cast<int>(current_width);
    rect.h = static_cast<int>(current_height);

    if (collider != nullptr) {
        collider->a = {pos_x, pos_y};
        collider->b = {pos_x, pos_y + current_height};
        collider->c = {pos_x + current_width, pos_y + current_height};
        collider->d = {pos_x + current_width, pos_y};
    }

    if (animator != nullptr) {
        if (animator->UpdateAnimator() != 0) {
            texture = managerHub->textureManager->LoadTexture(animator->current_frame, renderer);
        }
    }
}

void GameObject::FlipTexture(FlipMode flip_mode, bool flip_texture) {
    this->flip_mode = flip_mode;
    this->flip_texture = flip_texture;
}

void GameObject::SetPosition(float pos_x, float pos_y, float pos_z) {
    rect.x = static_cast<int>(pos_x);
    rect.y = static_cast<int>(pos_y);

    this->pos_x = pos_x;
    this->pos_y = pos_y;
    if (pos_z != NULL) {
        this->pos_z = pos_z;
    }

    float current_width = width * scale_x;
    float current_height = height * scale_y;

    if (collider != nullptr) {
        collider->a = {pos_x, pos_y};
        collider->b = {pos_x, pos_y + current_height};
        collider->c = {pos_x + current_width, pos_y + current_height};
        collider->d = {pos_x + current_width, pos_y};
    }
}

void GameObject::UpdatePosition(float delta_time) {
    if (body != nullptr) {
        rect.x += body->dx * delta_time * 100;
        rect.y += body->dy * delta_time * 100;

        pos_x = rect.x;
        pos_y = rect.y;

        if (collider != nullptr) {
            collider->a = {pos_x, pos_y};
            collider->b = {pos_x, pos_y + height};
            collider->c = {pos_x + width, pos_y + height};
            collider->d = {pos_x + width, pos_y};
        }
    }
}

void GameObject::SetScale(float scale_x, float scale_y) {
    if (scale_x <= 0 || scale_y <= 0) {
        cout << "GAMEOBJECT: (" << name << "). Cannot set scale <= 0. Original scale was kept!" << endl;
        return;
    }

    this->scale_x = scale_x;
    this->scale_y = scale_y;
}

void GameObject::SetScaleX(float scale_x) {
    if (scale_x <= 0) {
        cout << "GAMEOBJECT: (" << name << "). Cannot set scale <= 0. Original scale was kept!" << endl;
        return;
    }

    this->scale_x = scale_x;
}

void GameObject::SetScaleY(float scale_y) {
    if (scale_y <= 0) {
        cout << "GAMEOBJECT: (" << name << "). Cannot set scale <= 0. Original scale was kept!" << endl;
        return;
    }

    this->scale_y = scale_y;
}

void GameObject::AddCollider() {
    if (collider == nullptr) {
        collider = new Collider({pos_x, pos_y}, {pos_x, pos_x + height}, {pos_x + width, pos_y + height}, {pos_x + width, pos_y});
    }
    else {
        cout << "GAMEOBJECT: The object " << name << " already has a collider attached to it!" << endl;
    }
}

void GameObject::AddBody(float mass, bool use_gravity) {
    if (body == nullptr) {
        body = new Body(mass, use_gravity);
    }
    else {
        cout << "GAMEOBJECT: The object " << name << " already has a body attached to it!" << endl;
    }
}

void GameObject::AddAnimator() {
    if (animator == nullptr) {
        animator = new Animator();
    }
    else {
        cout << "GAMEOBJECT: The object " << name << " already has an animator attached to it!" << endl;
    }
}

GameObject::GameObject(const GameObject& other) {
    name = other.name;

    pos_x = other.pos_x;
    pos_y = other.pos_y;
    pos_z = other.pos_z;

    width = other.width;
    height = other.height;

    scale_x = other.scale_x;
    scale_y = other.scale_y;

    rotation = other.rotation;

    texture_filepath = other.texture_filepath;

    renderer = other.renderer;

    managerHub = &ManagerHub::GetInstance();

    // Recalculate SDL_Rect
    rect.x = static_cast<int>(pos_x);
    rect.y = static_cast<int>(pos_y);
    rect.w = static_cast<int>(width);
    rect.h = static_cast<int>(height);

    // Deep clone components
    collider = nullptr;

    body = nullptr;

    animator = nullptr;

    if (!texture_filepath.empty()) {
        texture = managerHub->textureManager->LoadTexture(texture_filepath, renderer);
        if (!texture) {
            printf("GAMEOBJECT (copy): Could not load texture! SDL_Error: %s\n", SDL_GetError());
        }
    } else {
        texture = nullptr;
    }
}

GameObject::~GameObject() {
    OnDeletion();

    if (collider != nullptr) {
        delete collider;
    }

    if (body != nullptr) {
        delete body;
    }

    if (animator != nullptr) {
        delete animator;
    }
}
