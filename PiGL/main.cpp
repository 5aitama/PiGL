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

#ifdef __APPLE__
#define CONTEXT_MAJOR 4
#define CONTEXT_MINOR 1
#else
#define CONTEXT_MAJOR 3
#define CONTEXT_MINOR 3
#endif

#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#elif __arm__
#include <GL/gl.h>
#endif

#include <GLFW/glfw3.h>

#include "WInfos.hpp"
#include "ShaderCompiler.hpp"

int main(int argc, const char * argv[]) {
    
    /* Initialise GLFW */
    if(!glfwInit()) {
        std::cout << "Failed when init GLFW..." << std::endl;
        return -1;
    }
    
    WInfos winfos(800, 600, "Hello world", CONTEXT_MAJOR, CONTEXT_MINOR);
    
    /* Version of OpenGL context */
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, winfos.context_version_major);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, winfos.context_version_minor);
    
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
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
    
    float verts[12] = {
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f,   // top left
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
    };
    
    float colors[12] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
    };
    
    GLubyte triangles[6] = {
        0, 1, 2,
        0, 2, 3,
    };
    
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24 , 0, GL_STATIC_DRAW);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 12, verts);
            glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 12, sizeof(float) * 12, colors);
    
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 6, 0, GL_STATIC_DRAW);
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(GLubyte) * 6, triangles);
    
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
            glEnableVertexAttribArray(0);
    
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(float) * 12));
            glEnableVertexAttribArray(1);
    
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glm::mat4 projection = glm::perspective(45.0f, static_cast<float>(winfos.width) / static_cast<float>(winfos.height), 0.1f, 100.0f);
    glm::mat4 view(1.0f);
    glm::mat4 model(1.0f);
    
    view = glm::lookAt(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    /*
     *  Delta time part
     */
    double last_time     = glfwGetTime();
    double delta_time    = 0.0f;
    
    double total_delta = 0.f;
    
    // FPS counter
    uint fps = 0;
    
    /* Loop */
    while(!glfwWindowShouldClose(window)) {
        
        double current_time    = glfwGetTime();
        delta_time      = current_time - last_time;
        last_time       = current_time;
        
        total_delta += delta_time;
        if(total_delta >= 1.0f) {
            std::cout << fps << "fps" << std::endl;
            fps = 0;
            total_delta -= 1.0f;
        } else {
            fps++;
        }
        
        /* Clear screen with a color... */
        glClearColor(0.26, 0.27, 0.28, 1);
        
        /* Clear sreen */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        model = glm::rotate(model, static_cast<float>(delta_time), glm::vec3(0.0f, 0.0f, 1.0f));
        
        /* Use shader */
        glUseProgram(shader.GetProgramID());
            glBindVertexArray(VAO);
        
                /* Send MVP matrices */
                glUniformMatrix4fv(glGetUniformLocation(shader.GetProgramID(), "M"), 1, GL_FALSE, glm::value_ptr(model));
                glUniformMatrix4fv(glGetUniformLocation(shader.GetProgramID(), "V"), 1, GL_FALSE, glm::value_ptr(view));
                glUniformMatrix4fv(glGetUniformLocation(shader.GetProgramID(), "P"), 1, GL_FALSE, glm::value_ptr(projection));
        
                /* Draw the mesh */
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
        
            glBindVertexArray(0);
        glUseProgram(0);
        
        /* Pool events */
        glfwPollEvents();
        
        /* Swap buffers */
        glfwSwapBuffers(window);
    }
    
    /* Delete vao! */
    if(glIsVertexArray(VAO) == GL_TRUE) {
        std::cout << "Delete vertex array object..." << std::endl;
        glDeleteVertexArrays(1, &VAO);
        std::cout << "Ok!\n" << std::endl;
    }
    
    /* Delete vbo! */
    if(glIsBuffer(VBO) == GL_TRUE) {
        std::cout << "Delete vertex buffer object..." << std::endl;
        glDeleteBuffers(1, &VBO);
        std::cout << "Ok!\n" << std::endl;
    }
    
    /* Delete ebo */
    if(glIsBuffer(EBO) == GL_TRUE) {
        std::cout << "Delete element buffer object..." << std::endl;
        glDeleteBuffers(1, &EBO);
        std::cout << "Ok!\n" << std::endl;
    }
    
    /* Terminate glfw */
    glfwTerminate();
    
    return 0;
}
