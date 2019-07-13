#include <glm/glm.hpp>

#ifndef SVERTEX_HPP
#define SVERTEX_HPP

struct SVertex {
    SVertex();
    SVertex(glm::vec3 position, glm::vec3 normal);
    SVertex(glm::vec3 position, glm::vec3 normal, glm::vec3 color);

    glm::vec3 position; // Position of the vertex.
    glm::vec3 normal; // Normal of the vertex.
    glm::vec3 color; // Color of the vertex.
};

#endif