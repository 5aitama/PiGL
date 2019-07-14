

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../SVertex/SVertex.hpp"
#include "../ShaderCompiler/ShaderCompiler.hpp"

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/gl.h>
#endif

#ifndef MESH_HPP
#define MESH_HPP

class Mesh {
public:
    Mesh(const ShaderCompiler& shader);
    ~Mesh();

    // Generte Vertex Buffer Object
    const void GenerateVBO();
    // Generate Vertex Array Object
    const void GenerateVAO();
    // Generate Element Buffer Object
    const void GenerateEBO();

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
    const size_t GetVerticesLength();
    // Get the triangle array length
    const size_t GetTrianglesLength();

    // Build the mesh
    const void BuildMesh();
    // Draw the mesh
    const void DrawMesh(const glm::mat4& m, const glm::mat4& v, const glm::mat4& p);

    // Get the shader object of the mesh
    const ShaderCompiler& GetShader();

protected:
    GLuint vbo = 0;
    GLuint vao = 0;
    GLuint ebo = 0;

    SVertex* vertices = nullptr;
    size_t vertices_length = 0;

    unsigned short* triangles = nullptr;
    size_t triangles_length = 0;

    ShaderCompiler shader;
};

#endif