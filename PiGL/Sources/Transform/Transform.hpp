#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#ifndef GLM_FORCE_LEFT_HANDED
#define GLM_FORCE_LEFT_HANDED
#endif

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

class Transform 
{
public:
    Transform();
    ~Transform();
    
    // Return a Quaternion from euleur angles
    const glm::quat QuatFromEuleurAngles(const glm::vec3& euleurAngles);

    // Return the position
    const glm::vec3& GetPosition() const;
    // Return the euleurAngles
    const glm::vec3& GetEuleurAngles() const;
    // Return the scale
    const glm::vec3& GetScale() const;
    // Return the quaternion
    const glm::quat& GetQuaternion() const;

    // Return the model matrix
    glm::mat4 GetMatrix() const;

    // Calculate the model matrix
    virtual const glm::mat4 CalculateMatrix();

    // Translate the transform
    void Translate(const glm::vec3& direction);
    // Rotate the transform
    void Rotate(const glm::vec3& euleurAngles);
    // Scale the transform
    void Scale(const glm::vec3& s);

    glm::vec3 GetForward() const;

    // Assign the position
    void SetPosition    (const glm::vec3& position);
    // Assign the euleur angles
    void SetEuleurAngles(const glm::vec3& euleurAngles);
    // Assign the scale
    void SetScale       (const glm::vec3& scale);
    // Assign the quaternion
    void SetQuaternion  (const glm::quat& quaternion);

private:
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