#include "Camera.hpp"

Camera::Camera() : Transform(), projection(), screen_width(0), screen_height(0), near(0.f), far(0.f), ratio(0.f), fov(0.f)
{ /* ... */ }

Camera::Camera(const int& sw, const int& sh, const float& fov, const float& near, const float& far)
    : Transform(), projection(), screen_width(sw), screen_height(sh), near(near), far(far), ratio(static_cast<float>(sw) / static_cast<float>(sh)), fov(fov)
{ 
    CalculateProjection();
}

Camera::~Camera() 
{ /* ... */ }

const glm::mat4 Camera::CalculateMatrix() {
    return glm::lookAt(GetPosition(), GetPosition() + GetQuaternion() * glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::SetScreenSize(const int& width, const int& height)
{
    screen_width = width;
    screen_height = height;

    // Recalculate ratio, and projection matrix
    SetRatio(static_cast<float>(screen_width) / static_cast<float>(screen_height));
}

void Camera::SetNear(const float& near) 
{
    this->near = near;
    CalculateProjection();
}


void Camera::SetFar(const float& far)
{
    this->far = far;
    CalculateProjection();
}

void Camera::SetFov(const float& fov)
{
    this->fov = fov;
    CalculateProjection();
}

void Camera::SetRatio(const float& ratio) 
{
    this->ratio = ratio;
    CalculateProjection();
}

void Camera::CalculateProjection()
{
    projection = glm::perspective(fov, ratio, near, far);
}

const glm::mat4 Camera::GetProjectionMatrix() const
{
    return projection;
}