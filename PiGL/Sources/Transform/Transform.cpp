#include "Transform.hpp"

Transform::Transform() 
    : position(0.f), scale(1.f), euleurAngles(0.f), quaternion(QuatFromEuleurAngles(euleurAngles)), 
    m_rotation(1.f), m_scale(1.f), m_translation(1.f), m_model(CalculateMatrix(m_translation, m_rotation, m_scale))
{ /* ... */ }

const glm::quat& Transform::QuatFromEuleurAngles(const glm::vec3& euleurAngles) {
    glm::quat qx(glm::vec4(1.f, 0.f, 0.f, euleurAngles.x));
    glm::quat qy(glm::vec4(0.f, 1.f, 0.f, euleurAngles.y));
    glm::quat qz(glm::vec4(0.f, 0.f, 1.f, euleurAngles.z));
    return (qx * qy * qz);
}

const glm::vec3& Transform::GetPosition() 
{
    return position;
}

const glm::vec3& Transform::GetEuleurAngles() 
{
    return euleurAngles;
}

const glm::vec3& Transform::GetScale() 
{
    return scale;
}

const glm::quat& Transform::GetQuaternion() 
{
    return quaternion;
}

const glm::mat4& Transform::GetMatrix() 
{
    return m_model;
}

const glm::mat4& Transform::CalculateMatrix(const glm::mat4& t, const glm::mat4& r, const glm::mat4& s) 
{
    return (t * r * s);
}

void Transform::Translate(const glm::vec3& direction) 
{
    m_translation = glm::translate(m_translation, direction);
    m_model = CalculateMatrix(m_translation, m_rotation, m_scale);
}

void Transform::Rotate(const glm::vec3& euleurAngles) 
{
    m_rotation = glm::toMat4(QuatFromEuleurAngles(this->euleurAngles + euleurAngles));
    m_model = CalculateMatrix(m_translation, m_rotation, m_scale);
}

void Transform::Scale(const glm::vec3& scale) 
{
    m_scale = glm::scale(m_scale, scale);
    m_model = CalculateMatrix(m_translation, m_rotation, m_scale);
}