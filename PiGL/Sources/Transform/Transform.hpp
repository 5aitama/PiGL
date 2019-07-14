#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

class Transform 
{
public:
    Transform();
    ~Transform();

    // Return a Quaternion from euleur angles
    const glm::quat& QuatFromEuleurAngles(const glm::vec3& euleurAngles);

    // Return the position
    const glm::vec3& GetPosition();
    // Return the euleurAngles
    const glm::vec3& GetEuleurAngles();
    // Return the scale
    const glm::vec3& GetScale();
    // Return the quaternion
    const glm::quat& GetQuaternion();

    // Return the model matrix
    const glm::mat4& GetMatrix();

    // Calculate the model matrix
    const glm::mat4& CalculateMatrix(const glm::mat4& t, const glm::mat4& r, const glm::mat4& s);

    // Translate the transform
    void Translate(const glm::vec3& direction);
    // Rotate the transform
    void Rotate(const glm::vec3& euleurAngles);
    // Scale the transform
    void Scale(const glm::vec3& s);

protected:
    // The position (in world) of the transform
    glm::vec3 position;
    // The scale of the transform
    glm::vec3 scale;
    // The euleurs angle of quaternion
    glm::vec3 euleurAngles;
    // The quaternion of the transform
    glm::quat quaternion;

    // The model matrix
    glm::mat4 m_model;

    // The translation matrix
    glm::mat4 m_translation;
    // The rotation matrix
    glm::mat4 m_rotation;
    // The scale matrix
    glm::mat4 m_scale;
};

#endif