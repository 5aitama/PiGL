//
//  ShaderCompiler.hpp
//  PiGL
//
//  Created by Alex Sb on 12/07/2019.
//  Copyright © 2019 Alex Sb. All rights reserved.
//

#define GL_SILENCE_DEPRECATION

#ifndef ShaderCompiler_hpp
#define ShaderCompiler_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include <GL/glew.h>

#ifndef __arm__
    #include <OpenGL/gl3.h>
#else
    #include <GL/gl.h>
#endif

class ShaderCompiler {
public:
     ShaderCompiler(const std::string& vertSrc, const std::string& fragSrc);
    ~ShaderCompiler();
    
    void Compile();
    const GLuint GetProgramID();
    const bool IsCompiled();
private:
    bool compiled;
    GLuint programID;
    GLuint v_shader;
    GLuint f_shader;
    std::string vertSrc;
    std::string fragSrc;
};

#endif /* ShaderCompiler_hpp */
