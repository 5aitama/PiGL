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
    
    void Compile();
    GLuint GetProgramID() const;
    bool IsCompiled() const;
private:
    bool compiled;
    GLuint programID;
    GLuint v_shader;
    GLuint f_shader;
    std::string vertSrc;
    std::string fragSrc;
};

#endif /* Shader_hpp */
