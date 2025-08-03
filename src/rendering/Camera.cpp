#include "Camera.h"

void Camera::Move(float dx, float dy) {
    x += dx;
    y += dy;
}

void Camera::CenterOn(float worldX, float worldY) {
    x = worldX - (screenWidth / 2.0f) / zoom;
    y = worldY - (screenHeight / 2.0f) / zoom;
}

void Camera::CenterOnObject(string name) {
    GameObject* object = managerHub->entityManager->FindGameObjectByName(name);
    float object_x = object->pos_x;
    float object_y = object->pos_y;

    CenterOn(object_x, object_y);
}

void Camera::ToggleSmoothFollow(float speed, string name) {
    is_following = !is_following;
    lerp_speed = speed;

    if (name != "") {
        target_object = managerHub->entityManager->FindGameObjectByName(name);
    }
}

void Camera::StartCamera(ManagerHub* managerHub) {
    this->managerHub = managerHub;
}

void Camera::UpdateCamera(float deltaTime) {
    if (target_zoom != zoom) {
        zoom += (target_zoom - zoom) * zoom_speed * deltaTime;

        if (zoom > target_zoom && zoom_in) {
            zoom_in = false;
            zoom = target_zoom;
        }
        if (zoom < target_zoom && zoom_out) {
            zoom_out = false;
            zoom = target_zoom;
        }
        if (zoom < 0) {
            zoom = 0.01f;
        }
    }
    if (is_following && target_object) {
        float target_x = target_object->pos_x;
        float target_y = target_object->pos_y;

        float desired_x = target_x - (screenWidth / 2.0f) / zoom;
        float desired_y = target_y - (screenHeight / 2.0f) / zoom;

        x += (desired_x - x) * (1.0f - exp(-lerp_speed * deltaTime));
        y += (desired_y - y) * (1.0f - exp(-lerp_speed * deltaTime));
    }
}
