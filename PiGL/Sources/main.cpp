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

#include "WInfos/WInfos.hpp"
#include "ShaderCompiler/ShaderCompiler.hpp"

int w_width = 800;
int w_height = 600;
glm::mat4 projection;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    w_width = width;
    w_height = height;
    glViewport(0, 0, width, height);
    projection = glm::perspective(45.0f, static_cast<float>(w_width) / static_cast<float>(w_height), 0.1f, 100.0f);
}

int main(int argc, const char * argv[]) {
    w_width = 800;
    w_height = 600;

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
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    glViewport(0, 0, winfos.width, winfos.height);
    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);
    glEnable(GL_DEPTH_TEST);

    // std::cout << glGetString(GL_VERSION) << std::endl;

    ShaderCompiler shader("PiGL/Shaders/basic.vertex", "PiGL/Shaders/basic.fragment");
    shader.Compile();

    // Check if shader is compiled successfully
    if(!shader.IsCompiled()) return -1;
    
    glm::vec3 verts[24] = {

        glm::vec3(-0.5f, -0.5f, -0.5f), // 0
        glm::vec3(-0.5f,  0.5f, -0.5f), // 1
        glm::vec3( 0.5f,  0.5f, -0.5f), // 2
        glm::vec3( 0.5f, -0.5f, -0.5f), // 3
        
        glm::vec3( 0.5f, -0.5f, -0.5f), // 3
        glm::vec3( 0.5f,  0.5f, -0.5f), // 2
        glm::vec3( 0.5f,  0.5f,  0.5f), // 6
        glm::vec3( 0.5f, -0.5f,  0.5f), // 7
        
        glm::vec3( 0.5f, -0.5f,  0.5f), // 7
        glm::vec3( 0.5f,  0.5f,  0.5f), // 6
        glm::vec3(-0.5f,  0.5f,  0.5f), // 5
        glm::vec3(-0.5f, -0.5f,  0.5f), // 4
        
        glm::vec3(-0.5f, -0.5f,  0.5f), // 4
        glm::vec3(-0.5f,  0.5f,  0.5f), // 5
        glm::vec3(-0.5f,  0.5f, -0.5f), // 1
        glm::vec3(-0.5f, -0.5f, -0.5f), // 0
        
        glm::vec3(-0.5f,  0.5f, -0.5f), // 1
        glm::vec3(-0.5f,  0.5f,  0.5f), // 5
        glm::vec3( 0.5f,  0.5f,  0.5f), // 6
        glm::vec3( 0.5f,  0.5f, -0.5f), // 2
        
        glm::vec3(-0.5f, -0.5f,  0.5f), // 4
        glm::vec3(-0.5f, -0.5f, -0.5f), // 0
        glm::vec3( 0.5f, -0.5f, -0.5f), // 3
        glm::vec3( 0.5f, -0.5f,  0.5f), // 7
    };
    
    glm::vec3 norms[24] = {
        glm::vec3( 0.0f,  0.0f, -1.0f),
        glm::vec3( 0.0f,  0.0f, -1.0f),
        glm::vec3( 0.0f,  0.0f, -1.0f),
        glm::vec3( 0.0f,  0.0f, -1.0f),
        
        glm::vec3( 1.0f,  0.0f,  0.0f),
        glm::vec3( 1.0f,  0.0f,  0.0f),
        glm::vec3( 1.0f,  0.0f,  0.0f),
        glm::vec3( 1.0f,  0.0f,  0.0f),
        
        glm::vec3( 0.0f,  0.0f,  1.0f),
        glm::vec3( 0.0f,  0.0f,  1.0f),
        glm::vec3( 0.0f,  0.0f,  1.0f),
        glm::vec3( 0.0f,  0.0f,  1.0f),
        
        glm::vec3(-1.0f,  0.0f,  0.0f),
        glm::vec3(-1.0f,  0.0f,  0.0f),
        glm::vec3(-1.0f,  0.0f,  0.0f),
        glm::vec3(-1.0f,  0.0f,  0.0f),
        
        glm::vec3( 0.0f,  1.0f,  0.0f),
        glm::vec3( 0.0f,  1.0f,  0.0f),
        glm::vec3( 0.0f,  1.0f,  0.0f),
        glm::vec3( 0.0f,  1.0f,  0.0f),
        
        glm::vec3( 0.0f, -1.0f,  0.0f),
        glm::vec3( 0.0f, -1.0f,  0.0f),
        glm::vec3( 0.0f, -1.0f,  0.0f),
        glm::vec3( 0.0f, -1.0f,  0.0f),
    };
    
    glm::vec3 colors[24] = {
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
    };
    
    GLubyte triangles[36] = {
        0 + (0 * 4), 1 + (0 * 4), 2 + (0 * 4), 0 + (0 * 4), 2 + (0 * 4), 3 + (0 * 4),
        0 + (1 * 4), 1 + (1 * 4), 2 + (1 * 4), 0 + (1 * 4), 2 + (1 * 4), 3 + (1 * 4),
        0 + (2 * 4), 1 + (2 * 4), 2 + (2 * 4), 0 + (2 * 4), 2 + (2 * 4), 3 + (2 * 4),
        0 + (3 * 4), 1 + (3 * 4), 2 + (3 * 4), 0 + (3 * 4), 2 + (3 * 4), 3 + (3 * 4),
        0 + (4 * 4), 1 + (4 * 4), 2 + (4 * 4), 0 + (4 * 4), 2 + (4 * 4), 3 + (4 * 4),
        0 + (5 * 4), 1 + (5 * 4), 2 + (5 * 4), 0 + (5 * 4), 2 + (5 * 4), 3 + (5 * 4),
    };
    
    size_t size_of_vert_bytes = sizeof(float) * 3 * 24;
    size_t size_of_norm_bytes = sizeof(float) * 3 * 24;
    size_t size_of_colo_bytes = sizeof(float) * 3 * 24;
    size_t size_of_tris_bytes = sizeof(GLubyte) * 36;
    
    size_t total_size = size_of_vert_bytes + size_of_norm_bytes + size_of_colo_bytes;
    
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glBufferData(GL_ARRAY_BUFFER, total_size , 0, GL_STATIC_DRAW);
            glBufferSubData(GL_ARRAY_BUFFER, 0, size_of_vert_bytes, verts);
            glBufferSubData(GL_ARRAY_BUFFER, size_of_vert_bytes, size_of_colo_bytes, colors);
            glBufferSubData(GL_ARRAY_BUFFER, size_of_vert_bytes + size_of_colo_bytes, size_of_norm_bytes, norms);
    
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_of_tris_bytes, 0, GL_STATIC_DRAW);
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size_of_tris_bytes, triangles);
    
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
            glEnableVertexAttribArray(0);
    
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(size_of_vert_bytes));
            glEnableVertexAttribArray(1);
    
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(size_of_vert_bytes + size_of_colo_bytes));
            glEnableVertexAttribArray(2);
    
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    
    // glfwGetFramebufferSize(window, &width, &height);
    projection = glm::perspective(45.0f, static_cast<float>(w_width) / static_cast<float>(w_height), 0.1f, 100.0f);
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
        
        model = glm::rotate(model, static_cast<float>(delta_time), glm::vec3(0.25f, 0.50f, 1.0f));
        
        /* Use shader */
        glUseProgram(shader.GetProgramID());
            glBindVertexArray(VAO);
        
                /* Send MVP matrices */
                glUniformMatrix4fv(glGetUniformLocation(shader.GetProgramID(), "M"), 1, GL_FALSE, glm::value_ptr(model));
                glUniformMatrix4fv(glGetUniformLocation(shader.GetProgramID(), "V"), 1, GL_FALSE, glm::value_ptr(view));
                glUniformMatrix4fv(glGetUniformLocation(shader.GetProgramID(), "P"), 1, GL_FALSE, glm::value_ptr(projection));
        
                /* Draw the mesh */
                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
        
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
