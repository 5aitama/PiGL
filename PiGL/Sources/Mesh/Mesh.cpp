#include "Mesh.hpp"

Mesh::Mesh() 
    : Transform(), vertices(nullptr), vertices_length(0), triangles(nullptr), triangles_length(0), vao(0), vbo(0), ebo(0), shader()
    { /* ... */ }

Mesh::Mesh(const Shader& shader) 
    : Transform(), vertices(nullptr), vertices_length(0), triangles(nullptr), triangles_length(0), vao(0), vbo(0), ebo(0), shader(shader)
    { /* ... */ }

Mesh::~Mesh() 
{ 
    if(glIsVertexArray(vao) == GL_TRUE) glDeleteVertexArrays(1, &vao);
    if(glIsBuffer(vbo) == GL_TRUE) glDeleteBuffers(1, &vbo);
    if(glIsBuffer(ebo) == GL_TRUE) glDeleteBuffers(1, &ebo);
}

void Mesh::GenerateVBO() 
{
    std::cout << "Generate VBO..." << std::endl;
    if(glIsBuffer(vbo) == GL_TRUE) glDeleteBuffers(1, &vbo);
    glGenBuffers(1, &vbo);
}

const GLuint& Mesh::GetVBO() const
{
    return vbo;
}

void Mesh::GenerateVAO() 
{
    std::cout << "Generate VAO..." << std::endl;
    if(glIsVertexArray(vao) == GL_TRUE) glDeleteVertexArrays(1, &vao);
    glGenVertexArrays(1, &vao);
}

const GLuint& Mesh::GetVAO() const
{
    return vao;
}

void Mesh::GenerateEBO() 
{
    std::cout << "Generate EBO..." << std::endl;
    if(glIsBuffer(ebo) == GL_TRUE) glDeleteBuffers(1, &ebo);
    glGenBuffers(1, &ebo);
}

const GLuint& Mesh::GetEBO() const
{
    return ebo;
}

void Mesh::SetVertices(SVertex* vertices, const size_t& length) 
{
    this->vertices = vertices;
    vertices_length = length;
}

void Mesh::SetTriangles(unsigned short* triangles, const size_t& length) 
{
    this->triangles = triangles;
    triangles_length = length;
}

const SVertex* Mesh::GetVertices() 
{
    return vertices;
}

const unsigned short* Mesh::GetTriangles() 
{
    return triangles;
}

size_t Mesh::GetVerticesLength() const
{
    return vertices_length;
}

size_t Mesh::GetTrianglesLength() const
{
    return triangles_length;
}

const Shader& Mesh::GetShader() const
{
    return shader;
}

void Mesh::BuildMesh()
{
    // Check if shader is compiled
    if(!shader.IsCompiled()) 
    {
        std::cout << "Compile shader..." << std::endl;
        shader.Compile();
        if(!shader.IsCompiled()) 
        {
            std::cout << "Can't build mesh, shader is not compiled!" << std::endl;
            return;
        }
    }

    // Check if object need to initialize
    GLboolean need_init_vbo = !glIsBuffer(GetVBO());
    GLboolean need_init_ebo = !glIsBuffer(GetEBO());
    GLboolean need_init_vao = !glIsVertexArray(GetVAO());

    // Generate object of they aren't generated...
    if(need_init_vbo) GenerateVBO();
    if(need_init_ebo) GenerateEBO();
    if(need_init_vao) GenerateVAO();

    // vertex, normal, color array from our SVertex array
    glm::vec3 extracted_v[vertices_length];
    glm::vec3 extracted_c[vertices_length];
    glm::vec3 extracted_n[vertices_length];

    // Extract Vertex, Normal and Color from SVertex array
    for(size_t i = 0; i < vertices_length; i++) 
    {
        extracted_v[i] = vertices[i].position;
        extracted_n[i] = vertices[i].normal;
        extracted_c[i] = vertices[i].color;
    }

    // The size of each extracted array in bytes
    size_t size_bytes = sizeof(glm::vec3) * vertices_length;

    // The vbo total size in bytes
    size_t vbo_size = sizeof(SVertex) * vertices_length;

    // The size of triangles array in bytes
    size_t size_tris_bytes = sizeof(unsigned short) * triangles_length;

    glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
            glBufferData(GL_ARRAY_BUFFER, vbo_size , 0, GL_STATIC_DRAW);
            glBufferSubData(GL_ARRAY_BUFFER, 0, size_bytes, extracted_v);
            glBufferSubData(GL_ARRAY_BUFFER, size_bytes, size_bytes, extracted_c);
            glBufferSubData(GL_ARRAY_BUFFER, size_bytes + size_bytes, size_bytes, extracted_n);
    
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_tris_bytes, 0, GL_STATIC_DRAW);
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size_tris_bytes, triangles);
    
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
            glEnableVertexAttribArray(0);
    
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(size_bytes));
            glEnableVertexAttribArray(1);
    
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(size_bytes + size_bytes));
            glEnableVertexAttribArray(2);
    
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    shader.Use();
    shader.SetInt("material.diffuse", 0);
    shader.SetInt("material.specular", 1);
    shader.Unuse();
}

void Mesh::DrawMesh(const Camera& camera) const
{
    // Use the shader
    shader.Use();

    shader.SetVec3("light.direction", glm::vec3(1.0f, 0.0f, -1.0f));
    shader.SetVec3("viewPos", camera.GetPosition());

    // light properties
    shader.SetVec3("light.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
    shader.SetVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
    shader.SetVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

    // material properties
    shader.SetFloat("material.shininess", 50.0f);
    shader.SetVec3("material.diffuse", glm::vec3(1.0f));
    shader.SetVec3("material.specular", glm::vec3(1.0f));

    shader.SetMat4("M", glm::mat4(1.0f));

    // Lock vao
    glBindVertexArray(vao);

    /* Send MVP matrices */
    shader.SetMat4("M", GetMatrix());
    shader.SetMat4("V", camera.GetMatrix());
    shader.SetMat4("P", camera.GetProjectionMatrix());

    /* Draw the mesh */
    glDrawElements(GL_TRIANGLES, triangles_length, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));

    // Unlock vao
    glBindVertexArray(0);

    shader.Unuse();
}