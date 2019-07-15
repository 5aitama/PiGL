#include "cube.hpp"

const SVertex Cube::base_vertices[8] = {
    // Face Z-
    SVertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0, 0, -1), glm::vec3(1, 1, 1)),
    SVertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0, 0, -1), glm::vec3(1, 1, 1)),
    SVertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3(0, 0, -1), glm::vec3(1, 1, 1)),
    SVertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3(0, 0, -1), glm::vec3(1, 1, 1)),

    // Face Z+
    SVertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0, 0, -1), glm::vec3(1, 1, 1)),
    SVertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0, 0, -1), glm::vec3(1, 1, 1)),
    SVertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3(0, 0, -1), glm::vec3(1, 1, 1)),
    SVertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3(0, 0, -1), glm::vec3(1, 1, 1)),
};

Cube::Cube(const int& i)
    : IGameObject(), i(i) 
{ 

}

Cube::~Cube() 
{ /* ... */ }

void Cube::OnBeforeInit() {
    /* Compile shader */
    shader.Compile();
}

void Cube::OnInit() {

    /* Vertex of the cube for each faces*/
    SVertex vertices[24] = {
        base_vertices[0], base_vertices[1], base_vertices[2], base_vertices[3], // Face Z-
        base_vertices[3], base_vertices[2], base_vertices[6], base_vertices[7], // Face X+
        base_vertices[7], base_vertices[6], base_vertices[5], base_vertices[4], // Face Z+
        base_vertices[4], base_vertices[5], base_vertices[1], base_vertices[0], // Face X-
        base_vertices[1], base_vertices[5], base_vertices[6], base_vertices[2], // Face Y+
        base_vertices[4], base_vertices[0], base_vertices[3], base_vertices[7]  // Face Y-
    };

    /* Normal for each faces of the cube */
    const glm::vec3 face_normals[6] = {
        glm::vec3( 0.0f,  0.0f, -1.0f),
        glm::vec3( 1.0f,  0.0f,  0.0f),
        glm::vec3( 0.0f,  0.0f,  1.0f),
        glm::vec3(-1.0f,  0.0f,  0.0f),
        glm::vec3( 0.0f,  1.0f,  0.0f),
        glm::vec3( 0.0f, -1.0f,  0.0f),
    };

    for(size_t i = 0; i < 24; i++) {
        vertices[i].normal = face_normals[i / 4];
    }

    unsigned short triangles[36]; // Triangles of the cube

    /* Calculate triangles of each face of the cube */
    for(unsigned short i = 0; i < 36; i += 6) {
        const unsigned short index = (i / 6) * 4;

        triangles[i + 0] = 0 + index;
        triangles[i + 1] = 1 + index;
        triangles[i + 2] = 2 + index;

        triangles[i + 3] = 0 + index;
        triangles[i + 4] = 2 + index;
        triangles[i + 5] = 3 + index;
    }

    // Assign vertices
    SetVertices(vertices, 24);

    // Assign triangles
    SetTriangles(triangles, 36);

    // Build the mesh
    BuildMesh();

    // Set the position of the cube
    SetPosition(glm::vec3((-5.0f + i) * 1.8f, 0.0f, 10.0f));

    // Set the rotation of the cube
    SetEuleurAngles(glm::vec3(45.0f, 0.0f, 0.0f));
    
}

void Cube::BeforeDrawMesh(const Camera& camera) const {
    glm::vec3 color(1.0f);

    if(i % 3 == 0) {
        color = glm::vec3(1.0f, 0.0f, 0.0f);
    } else if(i % 3 == 1) {
        color = glm::vec3(0.0f, 1.0f, 0.0f);
    } else {
        color = glm::vec3(0.0f, 0.0f, 1.0f);
    }

    shader.Use();

    shader.SetVec3("material.diffuse", color);
    shader.SetVec3("material.specular", color);
    shader.SetFloat("material.shininess", i * 10);

    shader.Unuse();
}

void Cube::OnUpdate(const double& deltaTime) {
    // Rotate the cube :)
    Rotate(glm::vec3(1.0f, 1.0f * cos(glm::radians(static_cast<float>(i * 2))), 0.0f) * static_cast<float>(deltaTime));
}