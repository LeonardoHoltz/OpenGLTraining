#include "../Headers/camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

Camera::Camera() :
    position(0.5f, 0.0f, 10.0f),
    view_direction_n(0.0f, 0.0f, -1.0f),
    up_direction_v(0.0f, 1.0f, 0.0f),
    right_direction_u(1.0f, 0.0f, 0.0f),
    camera_velocity(5.0f),
    delta_time(0.0),
    fps(0)
{
}

glm::mat4 Camera::View() {
    return glm::lookAt(position, position + view_direction_n, up_direction_v);
}

glm::mat4 Camera::SetDefaultProjection() {
    return Projection(horizontal_fov, vertical_fov, near_plane, far_plane);
}

glm::mat4 Camera::Projection(float hfov, float vfov, float nearPlane, float farPlane) {
    hfov = glm::radians(hfov);
    vfov = glm::radians(vfov);
    float aspectRatio = glm::tan(hfov / 2.0f) / glm::tan(vfov / 2.0f);
    return glm::perspective(vfov, aspectRatio, nearPlane, farPlane);
}

void Camera::MoveCamera(glm::vec3 direction) {
    position = position + direction;
}

void Camera::ChangeCameraPosition(glm::vec3 newPosition) {
    position = newPosition;
}

void Camera::MoveCameraToRight() {
    MoveCamera(delta_time * camera_velocity * right_direction_u);
}

void Camera::MoveCameraToLeft() {
    MoveCamera(delta_time * camera_velocity * (-right_direction_u));
}

void Camera::MoveCameraBackwards() {
    MoveCamera(delta_time * camera_velocity * (-view_direction_n));
}

void Camera::MoveCameraForwards() {
    MoveCamera(delta_time * camera_velocity * view_direction_n);
}

void Camera::MoveCameraUpwards() {
    MoveCamera(delta_time * camera_velocity * up_direction_v);
}

void Camera::MoveCameraDownwards() {
    MoveCamera(delta_time * camera_velocity * (-up_direction_v));
}

void Camera::SetCameraVelocity(float new_velocity) {
    camera_velocity = new_velocity;
}

void Camera::Roll_Z(float angle) {
    right_direction_u = (right_direction_u * cos(angle)) + (up_direction_v * sin(angle));
    up_direction_v = (-1.0f * right_direction_u * sin(angle)) + (up_direction_v * cos(angle));
}
void Camera::Yaw_Y(float angle) {
    right_direction_u = (right_direction_u * cos(angle)) + (view_direction_n * sin(angle));
    view_direction_n = (-1.0f * right_direction_u * sin(angle)) + (view_direction_n * cos(angle));
}
void Camera::Pitch_X(float angle) {
    up_direction_v = (up_direction_v * cos(angle)) + (view_direction_n * sin(angle));
    view_direction_n = (-1.0f * up_direction_v * sin(angle)) + (view_direction_n * cos(angle));
}

void Camera::TurnCameraRight() {
    Yaw_Y(-1.0f * delta_time);
}

void Camera::TurnCameraLeft() {
    Yaw_Y(1.0f * delta_time);
}

void Camera::TurnCameraUpwards() {
    Pitch_X(-1.0f * delta_time);
}

void Camera::TurnCameraDownwards() {
    Pitch_X(1.0f * delta_time);
}

void Camera::TiltCameraRight() {
    Roll_Z(-1.0f * delta_time);
}

void Camera::TiltCameraLeft() {
    Roll_Z(1.0f * delta_time);
}

void Camera::CalculateFrameRate()
{
    static int frames = 0;
    static float lastTime = (float)glfwGetTime();
    static float lastFrameTime = 0.0f;
    float currentTime = (float)glfwGetTime();
    delta_time = currentTime - lastFrameTime; // for camera velocity
    lastFrameTime = currentTime;
    frames++;
    if (currentTime - lastTime >= 1.0f)
    {
        lastTime = currentTime;
        fps = (int)frames;
        frames = 0;
    }
}