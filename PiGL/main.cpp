//
//  main.cpp
//  PiGL
//
//  Created by Alex Sb on 11/07/2019.
//  Copyright © 2019 Alex Sb. All rights reserved.
//

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "WInfos.hpp"

#ifdef __arm__
    #define CONTEXT_MAJOR 3
    #define CONTEXT_MINOR 3
#else
    #define CONTEXT_MAJOR 4
    #define CONTEXT_MINOR 1
#endif

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
    #ifndef __arm__
        glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #endif
    
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
    
    /* Loop */
    while(!glfwWindowShouldClose(window)) {
        
        /* Clear with white color... */
        glClearColor(0.26, 0.27, 0.28, 1);
        
        /* Clear sreen */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        /* Pool events */
        glfwPollEvents();
        
        /* Swap buffers */
        glfwSwapBuffers(window);
    }
    
    /* Terminate glfw */
    glfwTerminate();
    
    return 0;
}
