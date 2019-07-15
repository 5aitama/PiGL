#include "Transform.hpp"

Transform::Transform() 
    : position(0.f), scale(1.f), euleurAngles(0.f), quaternion(QuatFromEuleurAngles(euleurAngles)), 
    m_rotation(1.f), m_scale(1.f), m_translation(1.f), m_model(1.0f)
{ /* ... */ }

Transform::~Transform() 
{ /* ... */ }

const glm::quat Transform::QuatFromEuleurAngles(const glm::vec3& euleurAngles) {
    return glm::quat((euleurAngles));
}

const glm::vec3& Transform::GetPosition() const
{
    return position;
}

const glm::vec3& Transform::GetEuleurAngles() const
{
    return euleurAngles;
}

const glm::vec3& Transform::GetScale() const
{
    return scale;
}

const glm::quat& Transform::GetQuaternion() const
{
    return quaternion;
}

glm::mat4 Transform::GetMatrix()  const
{
    return m_model;
}

const glm::mat4 Transform::CalculateMatrix() 
{
    glm::mat4 identity = glm::mat4(1.0f);
    
    identity = glm::translate(identity, position);
    identity = glm::scale(identity, scale);
    identity *= glm::toMat4(quaternion);

    return identity;
}

void Transform::Translate(const glm::vec3& direction) 
{
    position += direction;
    m_model = CalculateMatrix();
}

void Transform::Rotate(const glm::vec3& euleurAngles) 
{
    this->euleurAngles += euleurAngles;
    
    if(this->euleurAngles.x > 180.0f) this->euleurAngles.x -= 360.0f;
    if(this->euleurAngles.y > 180.0f) this->euleurAngles.y -= 360.0f;
    if(this->euleurAngles.z > 180.0f) this->euleurAngles.z -= 360.0f;

    if(this->euleurAngles.x < -180.0f) this->euleurAngles.x += 360.0f;
    if(this->euleurAngles.y < -180.0f) this->euleurAngles.y += 360.0f;
    if(this->euleurAngles.z < -180.0f) this->euleurAngles.z += 360.0f;

    quaternion = QuatFromEuleurAngles(this->euleurAngles);
    m_model = CalculateMatrix();
}

void Transform::Scale(const glm::vec3& scale) 
{
    this->scale += scale;
    m_model = CalculateMatrix();
}

glm::vec3 Transform::GetForward() const 
{
    return quaternion * glm::vec3(0.0f, 0.0f, 1.0f);
}