#ifndef MESH_HPP
#define MESH_HPP

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../SVertex/SVertex.hpp"
#include "../Shader/Shader.hpp"

#include "../Transform/Transform.hpp"
#include "../Camera/Camera.hpp"

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/gl.h>
#endif

class Mesh : public Transform 
{
public:
    Mesh();
    Mesh(const Shader& shader);
    ~Mesh();

    // Generte Vertex Buffer Object
    void GenerateVBO();
    // Generate Vertex Array Object
    void GenerateVAO();
    // Generate Element Buffer Object
    void GenerateEBO();

    // Return the VBO ID
    const GLuint& GetVBO();
    // Return the VAO ID
    const GLuint& GetVAO();
    // Return the EBO ID
    const GLuint& GetEBO();

    // Assign the vertex array of the mesh
    void SetVertices(SVertex* vertices, const size_t& length);
    // Assign the triangles array of the mesh
    void SetTriangles(unsigned short* triangles, const size_t& length);

    // Get the vertex array of the mesh
    const SVertex& GetVertices();
    // Get the triangle array of the mesh
    const unsigned short& GetTriangles();

    // Get the vertex array length
    size_t GetVerticesLength();
    // Get the triangle array length
    size_t GetTrianglesLength();

    // Build the mesh
    void BuildMesh();
    // Draw the mesh
    void DrawMesh(const Camera& camera) const;

    // Get the shader object of the mesh
    const Shader& GetShader();

protected:
    GLuint vbo;
    GLuint vao;
    GLuint ebo;

    SVertex* vertices;
    size_t vertices_length;

    unsigned short* triangles;
    size_t triangles_length;

    Shader shader;
};

#endif