//
//  Shader.cpp
//  PiGL
//
//  Created by Alex Sb on 12/07/2019.
//  Copyright © 2019 Alex Sb. All rights reserved.
//

#include "Shader.hpp"

Shader::Shader() :
    compiled(false),
    programID(0),
    v_shader(0),
    f_shader(0),
    vertSrc("PiGL/Shaders/default.vertex"),
    fragSrc("PiGL/Shaders/default.fragment")
{ /* ... */ }

Shader::Shader(const std::string& vertSrc, const std::string& fragSrc) :
    compiled(false),
    programID(0),
    v_shader(0),
    f_shader(0),
    vertSrc(vertSrc),
    fragSrc(fragSrc)
{ /* ... */ }

Shader::Shader(const Shader& shader) 
    : compiled(shader.compiled),
    programID(shader.programID),
    v_shader(shader.v_shader),
    f_shader(shader.f_shader),
    vertSrc(shader.vertSrc),
    fragSrc(shader.fragSrc)
{ 
    
}

Shader::~Shader() {
    if(glIsProgram(programID) == GL_TRUE) {
        glDeleteProgram(programID);
    }
    
    if(glIsShader(v_shader) == GL_TRUE) {
        glDeleteShader(v_shader);
    }
    
    if(glIsShader(f_shader) == GL_TRUE) {
        glDeleteShader(f_shader);
    }
}

const std::string ReadFile(const std::string& path) {
    std::string content;
    std::ifstream stream;
    stream.open(path);

    if(stream.is_open()) 
    {
        std::string line;
        while(std::getline(stream, line)) {
            content.append(line + '\n');
        }

        return content;
    }
    else
    {
        std::cout << "Error: Can't open file at ( " << path << ")" << std::endl;
        throw 0;
    }
}

bool Shader::IsCompiled() const {
    return compiled;
}

void Shader::Use() const {
    glUseProgram(GetProgramID());
}

void Shader::Unuse() const {
    glUseProgram(0);
}

void Shader::Compile() {

    compiled = false;

    // Read our shaders into the appropriate buffers
    std::string vertexSource = ReadFile(vertSrc);   // Get source code for vertex shader.
    std::string fragmentSource = ReadFile(fragSrc); // Get source code for fragment shader.

    // Create an empty vertex shader handle
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Send the vertex shader source code to GL
    // Note that std::string's .c_str is NULL character terminated.
    const GLchar *source = (const GLchar *)vertexSource.c_str();
    glShaderSource(vertexShader, 1, &source, 0);

    // Compile the vertex shader
    glCompileShader(vertexShader);

    GLint isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

        // We don't need the shader anymore.
        glDeleteShader(vertexShader);

        // Use the infoLog as you see fit.
        std::cout << (char*)infoLog.data() << std::endl;

        // In this simple program, we'll just leave
        return;
    }

    // Create an empty fragment shader handle
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Send the fragment shader source code to GL
    // Note that std::string's .c_str is NULL character terminated.
    source = (const GLchar *)fragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &source, 0);

    // Compile the fragment shader
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
        
        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
        
        // We don't need the shader anymore.
        glDeleteShader(fragmentShader);
        // Either of them. Don't leak shaders.
        glDeleteShader(vertexShader);
        
        // Use the infoLog as you see fit.
        std::cout << (char*)infoLog.data() << std::endl;
        
        // In this simple program, we'll just leave
        return;
    }

    // Vertex and fragment shaders are successfully compiled.
    // Now time to link them together into a program.
    // Get a program object.
    GLuint program = glCreateProgram();

    // Attach our shaders to our program
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    // Link our program
    glLinkProgram(program);

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);

    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

        // We don't need the program anymore.
        glDeleteProgram(program);
        // Don't leak shaders either.
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        // Use the infoLog as you see fit.
        std::cout << (char*)infoLog.data() << std::endl;

        // In this simple program, we'll just leave
        return;
    }

    // Always detach shaders after a successful link.
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);

    programID = program;
    v_shader = vertexShader;
    f_shader = fragmentShader;

    compiled = true;
}

void Shader::SetInt(const std::string& name, const int& value) const {
    glUniform1i(glGetUniformLocation(GetProgramID(), name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, const float& value) const {
    glUniform1f(glGetUniformLocation(GetProgramID(), name.c_str()), value);
}

void Shader::SetVec3(const std::string& name, const glm::vec3& value) const {
    glUniform3f(glGetUniformLocation(GetProgramID(), name.c_str()), value.x, value.y, value.z);
}

void Shader::SetVec4(const std::string& name, const glm::vec4& value) const {
    glUniform4f(glGetUniformLocation(GetProgramID(), name.c_str()), value.x, value.y, value.z, value.w);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& value) const {
    glUniformMatrix4fv(glGetUniformLocation(GetProgramID(), name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetMat3(const std::string& name, const glm::mat3& value) const {
    glUniformMatrix3fv(glGetUniformLocation(GetProgramID(), name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

GLuint Shader::GetProgramID() const {
    return programID;
}
