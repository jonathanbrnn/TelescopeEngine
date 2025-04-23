#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "../core/ManagerHub.h"
#include "../animation/Animator.h"
#include "Force.h"
#include "Body.h"
#include "Collider.h"

using namespace std;

struct Collision;
class ManagerHub;

enum FlipMode {
    FLIP_HORIZONTAL,
    FLIP_VERTICAL
};

// GAME OBJECT:

class GameObject {
    public:
        // The game objects name.
        // Must be unique. Used in the EntityManagers look up by name table and its Instantiate() method.
        string name;

        // POSITION:
        // The objects position in 2D space.
        float pos_x, pos_y;
        // The objects "depth".
        // The higher the value, the further back the object is placed.
        float pos_z;
        // The width and height of the object.
        float width, height;
        // The scale of the object (default=1).
        float scale_x, scale_y = 1;
        // The objects rotation.
        // (!) Currently not implemented.
        float rotation;

        SDL_Renderer* renderer;

        // Filepath to the image that should be used for the game objects texture, defines the appearance.
        string texture_filepath;
        // The objects texture.
        SDL_Texture* texture;

        // Wether or not the texture should be flipped.
        bool flip_texture;

        // How the texture should be flipped.
        FlipMode flip_mode;

        // STILL UNDER DEVELOPMENT - CURRENTLY ONLY ABLE TO FLIP EITHER (!) HORIZONTALLY OR VERTICALLY WITH ONE CALL.
        void FlipTexture(FlipMode flip_mode = FLIP_HORIZONTAL, bool flip_texture = true);

        // The area in which the texture is rendered. Defined by the pos_x, pos_y, width and height parameters.
        SDL_Rect rect;

        // Access to the ManagerHub. Used to access all Managers.
        ManagerHub* managerHub;

        // POSITION:
        // Set pos_x, pos_y and pos_z (pos_z DEFAULT=NULL).
        void SetPosition(float pos_x, float pos_y, float pos_z = NULL);
        // Updates the game objects position every frame with its bodies velocity. Is only called if it has a body.
        void UpdatePosition(float delta_time);

        // SCALE:
        // Set both scale_x and scale_y:
        void SetScale(float scale_x, float scale_y);
        // Set scale_x.
        void SetScaleX(float scale_x);
        // Set scale_y.
        void SetScaleY(float scale_y);

        // COLLISION:
        Collider* collider;

        // Adds a collider to the game object.
        // Currently a game object only supports one collider at a time.
        // (!) Currently colliders have the exact dimensions of the rect area.
        void AddCollider();

        // BODY:
        Body* body;

        // Adds a body to the game object.
        // A game object can only have one body.
        void AddBody(float mass, bool use_gravity);

        // ANIMATOR:
        Animator* animator;

        // Adds am animator to the game object.
        // A game object can only have one animator.
        void AddAnimator();

        // CONSTRUCTOR:
        // Set texture_filepath to "" to make it invisible.
        GameObject(SDL_Renderer* renderer, string name, float pos_x = 0, float pos_y = 0, float pos_z = 0, float width = 1,
            float height = 1, float rotation = 0, string texture_filepath = "/Users/admin/TelescopeEngine/media/sample_640×426.bmp");

        // Called before the first frame and after Start().
        // Checks if the game object is correctly configured.
        void CheckGameObject();

        // Calls ll relevant functions that need to be updated each frame.
        void UpdateGameObject();

        // Called before the first frame update.
        virtual void Start() {}

        // Called during every frame update.
        virtual void Update() {}

        // Can be called at anytime, from anywhere.
        // Is passed a code to determine which specific function should be called. Only used in derived classes.
        virtual void Whisper(int code) {}

        // Called when the game object collides.
        // Provides a collision object that contains information about: the contacts name, its impact velocity, the impact velocity of this object,
        // the side the contact is located at (TOP, BOTTOM, LEFT, RIGHT) and an approximation of the collision point.
        virtual void OnCollision(Collision collison) {}

        // Called upon deleting the game object from memory.
        // Use this to clean up any added properties.
        virtual void OnDeletion() {}

        virtual GameObject* Clone() const = 0;

        virtual ~GameObject();
};

#endif
