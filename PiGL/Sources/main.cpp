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
#define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#include <OpenGL/gl3.h>
#elif __arm__
#include <GL/gl.h>
#endif

#include <GLFW/glfw3.h>

#include "Camera/Camera.hpp"
#include "WInfos/WInfos.hpp"
#include "Shader/Shader.hpp"
#include "SVertex/SVertex.hpp"
#include "Mesh/Mesh.hpp"
#include "Scene/Scene.hpp"

#include "../Testing/cube.hpp"

int main() {

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

    /*
     *  Delta time part
     */
    double last_time     = glfwGetTime();
    double delta_time    = 0.0f;
    
    double total_delta = 0.f;
    
    // FPS counter
    unsigned short fps = 0;

    Scene scene(winfos, window);
    
    Shader shader;
    shader.Compile();

    for(int i = 0; i < 10; i++) 
    {
        Cube* cube = new Cube(i);
        cube->SetShader(shader);
        scene.AddGameObject(cube, "cube" + std::to_string(i));
    }
    
    /* Loop */
    while(!glfwWindowShouldClose(window)) 
    {
        
        // Get the current time
        double current_time    = glfwGetTime();

        // Calculate the delta of it
        delta_time      = current_time - last_time;

        // Set the last time to the current
        last_time       = current_time;
        
        // For fps
        total_delta += delta_time;

        // Write FPS in the console, and reset fps and total_delta.
        if(total_delta >= 1.0f) {
            std::cout << fps << "fps" << std::endl;
            fps = 0;
            total_delta -= 1.0f;
        } else {
            fps++;
        }

        scene.OnBeforeRenderGameObjects();
        scene.OnUpdate(delta_time);
        scene.OnRenderGameObjects();
    }
    
    /* Terminate glfw */
    glfwTerminate();
    
    return 0;
}
