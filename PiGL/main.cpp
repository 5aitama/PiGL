//
//  main.cpp
//  PiGL
//
//  Created by Alex Sb on 11/07/2019.
//  Copyright © 2019 Alex Sb. All rights reserved.
//

#define GL_SILENCE_DEPRECATION

#ifndef BUFFER_OFFSET
    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

#ifndef GLM_FORCE_LEFT_HANDED
    #define GLM_FORCE_LEFT_HANDED
#endif

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

#ifdef __arm__
    #define CONTEXT_MAJOR 3
    #define CONTEXT_MINOR 3
#else
    #define CONTEXT_MAJOR 4
    #define CONTEXT_MINOR 1
#endif

#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#endif

#include <GLFW/glfw3.h>

#include "WInfos.hpp"
#include "ShaderCompiler.hpp"

int main(int argc, const char * argv[]) {
    
    WInfos winfos(800, 600, "Hello world", CONTEXT_MAJOR, CONTEXT_MINOR);
    
    /* Initialise GLFW */
    if(!glfwInit()) {
        std::cout << "Failed when init GLFW..." << std::endl;
        return -1;
    }
    
    /* Version of OpenGL context */
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, winfos.context_version_major);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, winfos.context_version_minor);
    
    /* For Mac OS only? */
    // #ifndef __arm__
        glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //#endif
    
    /* Create window */
    GLFWwindow* window = glfwCreateWindow(winfos.width, winfos.height, winfos.title.c_str(), NULL, NULL);
    
    /* Check window */
    if(!window) {
        std::cout << "Erreur lors de la création de la fenetere!" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    /* Make the window s context current */
    glfwMakeContextCurrent(window);
    
    /* Init GLEW */
    glewInit();
    
    glViewport(0, 0, winfos.width, winfos.height);
    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);
    
    std::cout << glGetString(GL_VERSION) << std::endl;

    ShaderCompiler shader("Shaders/basic.vertex",
                          "Shaders/basic.fragment");
    shader.Compile();
    
    std::cout << "Shader is compiled ? " << shader.IsCompiled() << std::endl;
    
    float verts[9] = {
        -1.0f, -1.0f,  0.0f,
         0.0f, 1.0f,  0.0f,
         1.0f, -1.0f,  0.0f
    };
    
    float colors[9] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };
    
    GLuint vboID;
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9 * 2, 0, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 9, verts);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 9, sizeof(float) * 9, colors);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    GLuint vaoID;
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
    
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
            glEnableVertexAttribArray(0);
    
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(float) * 9));
            glEnableVertexAttribArray(1);
    
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    
    glm::mat4 projection = glm::perspective(45.0f, static_cast<float>(winfos.width) / static_cast<float>(winfos.height), 0.1f, 100.0f);
    glm::mat4 view(1.0f);
    glm::mat4 model(1.0f);
    
    view = glm::lookAt(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    float last_time     = static_cast<float>(glfwGetTime());
    float delta_time    = 0.0f;
    
    /* Loop */
    while(!glfwWindowShouldClose(window)) {
        
        float current_time    = static_cast<float>(glfwGetTime());
        delta_time      = current_time - last_time;
        last_time       = current_time;
        
        // std::cout << delta_time << std::endl;
        
        /* Clear with white color... */
        glClearColor(0.26, 0.27, 0.28, 1);
        
        /* Clear sreen */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        model = glm::rotate(model, delta_time, glm::vec3(0.0f, 0.0f, 1.0f));
        
        /* Use shader */
        glUseProgram(shader.GetProgramID());
            glBindVertexArray(vaoID);
                glUniformMatrix4fv(glGetUniformLocation(shader.GetProgramID(), "M"), 1, GL_FALSE, glm::value_ptr(model));
                glUniformMatrix4fv(glGetUniformLocation(shader.GetProgramID(), "V"), 1, GL_FALSE, glm::value_ptr(view));
                glUniformMatrix4fv(glGetUniformLocation(shader.GetProgramID(), "P"), 1, GL_FALSE, glm::value_ptr(projection));
                glDrawArrays(GL_TRIANGLES, 0, 3);
            glBindVertexArray(0);
        glUseProgram(0);
        
        /* Pool events */
        glfwPollEvents();
        
        /* Swap buffers */
        glfwSwapBuffers(window);
    }
    
    /* Delete vao! */
    if(glIsVertexArray(vaoID) == GL_TRUE) {
        std::cout << "Delete vertex array object..." << std::endl;
        glDeleteVertexArrays(1, &vaoID);
        std::cout << "Ok!\n" << std::endl;
    }
    
    /* Delete vbo! */
    if(glIsBuffer(vboID) == GL_TRUE) {
        std::cout << "Delete vertex buffer object..." << std::endl;
        glDeleteBuffers(1, &vboID);
        std::cout << "Ok!\n" << std::endl;
    }
    
    /* Terminate glfw */
    glfwTerminate();
    
    return 0;
}
