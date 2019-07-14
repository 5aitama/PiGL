#include "../Transform/Transform.hpp"

#ifndef CAMERA_HPP
#define CAMERA_HPP

class Camera : public Transform
{
public:
    Camera();
    ~Camera();

    // Set the size of the screen to the camera
    void SetScreenSize(const int& width, const int& height);

    // Set camera near
    void SetNear(const float& near);
    // Set camera far
    void SetFar(const float& fat);
    // Set camera ratio
    void SetRatio(const float& ratio);
    // Set camera fov
    void SetFov(const float& fov);

    // Calculate the projection matrix of the camera
    const glm::mat4& CalculateProjection();

    // Return the camera projection matrix
    const glm::mat4& GetProjectionMatrix();

protected:
    // Camera projection matrix
    glm::mat4 projection;
    
    // The width of screen
    int screen_width;
    // The height of screen
    int screen_height;

    // Camera Near
    float near;
    // Camera Far
    float far;
    // Camera Ratio
    float ratio;
    // Camera fov
    float fov;
};

#endif