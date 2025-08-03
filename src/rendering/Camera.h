#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include "../core/ManagerHub.h"

using namespace std;

class ManagerHub;

class Camera {
    public:
    Camera(int screenWidth, int screenHeight)
            : screenWidth(screenWidth), screenHeight(screenHeight) {}

    float x = 0;
    float y = 0;
    float zoom = 1.0f;

    tuple<float, float> GetCenter() { return {x + screenWidth / 2.0f / zoom, y + screenHeight / 2.0f / zoom}; }

    // Move the camera by dx and dy.
    void Move(float dx, float dy);

    // Centers on a point in the world immediatly.
    void CenterOn(float worldX, float worldY);

    // Centers on a specified game objects position immediatly.
    void CenterOnObject(string name);

    // Change the cameras zoom immediatly.
    void InstantZoom(float zoom) { this->zoom = zoom; }

    void SmoothZoom(float target_zoom, float zoom_speed) {
        this->target_zoom = target_zoom;
        this->zoom_speed = zoom_speed;

        if (target_zoom < zoom) {
            zoom_out = true;
        }
        else {
            zoom_in = true;
        }
    }

    // Makes the camera follow a specific game object at a specified speed.
    // Calling the function again stops the camera from following.
    // It is only necessary to provide the name of the object on the first toggle and when changing objects.
    void ToggleSmoothFollow(float speed = 0.1, string name = "");

    // Translates a point on screen to the respective world position.
    void CameraToWorld(int& x, int& y) { 
        x = x + screenWidth / zoom;
        y = y + screenHeight / zoom; 
    }

    // Called upon engine initialization.
    void StartCamera(ManagerHub* managerHub);

    // Responsible for updating the camera each frame.
    void UpdateCamera(float deltaTime);

    private:

    ManagerHub* managerHub;

    int screenWidth;
    int screenHeight;

    float target_zoom = 1.0f;
    float zoom_speed = 0.0f;
    bool zoom_out = false;
    bool zoom_in = false;

    bool is_following = false;
    GameObject* target_object = nullptr;
    float lerp_speed = 0.1;
};

#endif
