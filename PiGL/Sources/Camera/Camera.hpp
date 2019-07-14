#ifndef CAMERA_HPP
#define CAMERA_HPP

#ifndef GLM_FORCE_LEFT_HANDED
#define GLM_FORCE_LEFT_HANDED
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <stdio.h>

#include "../Transform/Transform.hpp"

class Camera : public Transform
{
public:
    Camera();
    Camera(const int& sw, const int& sh, const float& fov, const float& near, const float& far);
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
    void CalculateProjection();
    
    // Return the camera projection matrix
    const glm::mat4 GetProjectionMatrix() const;

    virtual const glm::mat4 CalculateMatrix();

private:
    
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