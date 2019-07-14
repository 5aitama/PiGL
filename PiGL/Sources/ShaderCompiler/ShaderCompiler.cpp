//
//  ShaderCompiler.cpp
//  PiGL
//
//  Created by Alex Sb on 12/07/2019.
//  Copyright © 2019 Alex Sb. All rights reserved.
//

#include "ShaderCompiler.hpp"

ShaderCompiler::ShaderCompiler(const std::string& vertSrc, const std::string& fragSrc) :
    vertSrc(vertSrc),
    fragSrc(fragSrc),
    programID(0),
    v_shader(0),
    f_shader(0),
    compiled(false)
{ /* ... */ }

ShaderCompiler::ShaderCompiler(const ShaderCompiler& shader) 
    : vertSrc(shader.vertSrc),
     fragSrc(shader.fragSrc),
     programID(0),
     v_shader(0),
     f_shader(0),
     compiled(false)
{ 
    Compile(); 
}

ShaderCompiler::~ShaderCompiler() {
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
    
    if(stream.is_open()) {
        std::string line;
        while(std::getline(stream, line)) {
            content.append(line + '\n');
        }
        
        return content;
    } else {
        std::cout << "Error: Can't open file at ( " << path << ")" << std::endl;
        throw 0;
    }
}

const bool ShaderCompiler::IsCompiled() {
    return compiled;
}

void ShaderCompiler::Compile() {
    
    compiled = false;
    
    // Read our shaders into the appropriate buffers
    std::string vertexSource = ReadFile(vertSrc);// Get source code for vertex shader.
    std::string fragmentSource = ReadFile(fragSrc);// Get source code for fragment shader.
    
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

const GLuint ShaderCompiler::GetProgramID() {
    return programID;
}
