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
    
    // Camera camera(winfos.width, winfos.height, 45.f, 0.1f, 100.0f);

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

    SVertex base_vertices[] = {
        // Face Z-
        SVertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0, 0, -1), glm::vec3(1, 1, 1)),
        SVertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0, 0, -1), glm::vec3(1, 1, 1)),
        SVertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3(0, 0, -1), glm::vec3(1, 1, 1)),
        SVertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3(0, 0, -1), glm::vec3(1, 1, 1)),

        // Face Z+
        SVertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0, 0, -1), glm::vec3(1, 1, 1)),
        SVertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0, 0, -1), glm::vec3(1, 1, 1)),
        SVertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3(0, 0, -1), glm::vec3(1, 1, 1)),
        SVertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3(0, 0, -1), glm::vec3(1, 1, 1)),
    };

    SVertex vertices[24] = {
        // Face Z-
        base_vertices[0], base_vertices[1], base_vertices[2], base_vertices[3],
        
        // Face X+
        base_vertices[3], base_vertices[2], base_vertices[6], base_vertices[7],
        
        // Face Z+
        base_vertices[7], base_vertices[6], base_vertices[5], base_vertices[4],
        
        // Face X-
        base_vertices[4], base_vertices[5], base_vertices[1], base_vertices[0],
        
        // Face Y+
        base_vertices[1], base_vertices[5], base_vertices[6], base_vertices[2],

        // Face Y-
        base_vertices[4], base_vertices[0], base_vertices[3], base_vertices[7],
    };

    /* Normal for each faces of the cube */
    glm::vec3 face_normals[6] = {
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, -1.0f, 0.0f),
    };

    for(size_t i = 0; i < 24; i++) {
        vertices[i].normal = face_normals[i / 4];
    }

    unsigned short triangles[36]; // Triangles of the cube

    /* Calculate triangles of each face of the cube */
    for(unsigned short i = 0; i < 36; i += 6) {
        unsigned short index = (i / 6) * 4;

        triangles[i + 0] = 0 + index;
        triangles[i + 1] = 1 + index;
        triangles[i + 2] = 2 + index;

        triangles[i + 3] = 0 + index;
        triangles[i + 4] = 2 + index;
        triangles[i + 5] = 3 + index;
    }

    Mesh mesh;
    mesh.SetVertices(vertices, 24);
    mesh.SetTriangles(triangles, 36);
    mesh.BuildMesh();

    /*
     *  Delta time part
     */
    double last_time     = glfwGetTime();
    double delta_time    = 0.0f;
    
    double total_delta = 0.f;
    
    // FPS counter
    unsigned short fps = 0;

    Scene scene(winfos, window);

    scene.AddMesh(&mesh, "MyMesh");
    
    /* Loop */
    while(!glfwWindowShouldClose(window)) {
        
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
