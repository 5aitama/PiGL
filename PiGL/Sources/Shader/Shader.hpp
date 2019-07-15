//
//  Shader.hpp
//  PiGL
//
//  Created by Alex Sb on 12/07/2019.
//  Copyright © 2019 Alex Sb. All rights reserved.
//

#define GL_SILENCE_DEPRECATION

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>

#ifdef __APPLE__
    #define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
    #include <OpenGL/gl3.h>
#else
    #include <GL/gl.h>
#endif

#ifndef Shader_hpp
#define Shader_hpp

class Shader {
public:
    Shader();
    Shader(const std::string& vertSrc, const std::string& fragSrc);
    Shader(const Shader& shader);
    ~Shader();
    
    // Compile the shader
    void Compile();

    // Return the program id
    GLuint GetProgramID() const;

    // Set int value in the shader
    void SetInt(const std::string& name, const int& value) const;
    // Set float value in the shader
    void SetFloat(const std::string& name, const float& value) const;
    // Set vec3 value in the shader
    void SetVec3(const std::string& name, const glm::vec3& value) const;
    // Set vec4 value in the shader
    void SetVec4(const std::string& name, const glm::vec4& value) const;
    // Set Matrix4x4 in the shader
    void SetMat4(const std::string& name, const glm::mat4& value) const;
    // Set Matrix3x3 in the shader
    void SetMat3(const std::string& name, const glm::mat3& value) const;

    // Is the shader is compiled or not
    bool IsCompiled() const;

    // Use the shader
    void Use() const;

    // Unuse the shader
    void Unuse() const;

private:
    bool compiled;
    GLuint programID;
    GLuint v_shader;
    GLuint f_shader;
    std::string vertSrc;
    std::string fragSrc;
};

#endif /* Shader_hpp */
