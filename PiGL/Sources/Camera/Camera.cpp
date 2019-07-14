#include "Camera.hpp"

Camera::Camera() 
    : near(0.1f), 
    far(100.0f),
    screen_width(800),
    screen_height(600),
    ratio(static_cast<float>(screen_width) / static_cast<float>(screen_height)), 
    projection(CalculateProjection())
{ /* ... */ }

Camera::~Camera() 
{

}

void Camera::SetScreenSize(const int& width, const int& height)
{
    screen_width = width;
    screen_height = height;

    // Recalculate camera ratio, and camera matrix
    SetRatio(static_cast<float>(screen_width) / static_cast<float>(screen_height));
}

void Camera::SetNear(const float& near) 
{
    this->near = near;

    // Recalculate projection matrix
    projection = CalculateProjection();
}

void Camera::SetFar(const float& far)
{
    this->far = far;

    // Recalculate projection matrix
    projection = CalculateProjection();
}

void Camera::SetFov(const float& fov)
{
    this->fov = fov;

    // Recalculate projection matrix
    projection = CalculateProjection();
}

void Camera::SetRatio(const float& ratio) 
{
    this->ratio = ratio;

    // Recalculate projection matrix
    projection = CalculateProjection();
}

const glm::mat4& Camera::CalculateProjection() 
{
    return glm::perspective(fov, ratio, near, far);
}

const glm::mat4& Camera::GetProjectionMatrix() 
{
    return projection;
}