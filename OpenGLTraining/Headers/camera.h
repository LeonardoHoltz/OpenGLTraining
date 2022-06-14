// camera.h
#ifndef CAMERA_H
#define CAMERA_H

#include <glm/mat4x4.hpp>


class Camera {
private:
    float horizontal_fov = 100.0f, vertical_fov = 60.0f;
    float near_plane = 0.5f, far_plane = 5000.0f;

public:
    glm::vec3 position;
    glm::vec3 view_direction_n;
    glm::vec3 up_direction_v;
    glm::vec3 right_direction_u;
    float camera_velocity;
    float delta_time;
    int fps;

    Camera();
    glm::mat4 View();
    glm::mat4 SetDefaultProjection();
    glm::mat4 Projection(float hfov, float vfov, float nearPlane, float farPlane);
    void MoveCamera(glm::vec3 direction);
    void ChangeCameraPosition(glm::vec3 newPosition);
    void MoveCameraToRight();
    void MoveCameraToLeft();
    void MoveCameraBackwards();
    void MoveCameraForwards();
    void MoveCameraUpwards();
    void MoveCameraDownwards();
    void SetCameraVelocity(float new_velocity);
    void Roll_Z(float angle);
    void Yaw_Y(float angle);
    void Pitch_X(float angle);
    void TurnCameraRight();
    void TurnCameraLeft();
    void TurnCameraUpwards();
    void TurnCameraDownwards();
    void TiltCameraRight();
    void TiltCameraLeft();

    void CalculateFrameRate();
};

#endif // CAMERA_H