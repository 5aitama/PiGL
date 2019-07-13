#include "SVertex.hpp"

SVertex::SVertex() 
    : position(0.f), normal(0.f), color(0.f) 
    { /* ... */ }

SVertex::SVertex(glm::vec3 position, glm::vec3 normal) 
    : position(position), normal(normal), color(0.f) 
    { /* ... */ }

SVertex::SVertex(glm::vec3 position, glm::vec3 normal, glm::vec3 color)
    : position(position), normal(normal), color(color) 
    { /* ... */ }