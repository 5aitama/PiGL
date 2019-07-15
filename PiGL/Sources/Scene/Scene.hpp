#ifndef SCENE_HPP
#define SCENE_HPP

#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Mesh/Mesh.hpp"
#include "../Camera/Camera.hpp"
#include "../WInfos/WInfos.hpp"
#include "../GameObject/GameObject.hpp"

class Scene {
public:
    Scene(const WInfos& winfos, GLFWwindow* window);
    
    virtual ~Scene();

    /* Add a gameObject */
    void AddGameObject(IGameObject* gameObject, const std::string& name);

    /* 
        This method is called before render all meshes.
        In this method you need to call all GL method like
        glClearColor(...) or/and glCleatBuffer(...) ...
     */
    virtual void OnBeforeRenderGameObjects();

    /*
        This method is called to do some translation, rotation
        scale or anything you want on gameObject or anything
        you want :).
        Is called before all meshes rendered
     */
    virtual void OnUpdate(const double& deltaTime);

    /* 
        This method is called to render all meshes in 
        this scene to the screen
    */
    virtual void OnRenderGameObjects();

private:
    std::map<std::string, IGameObject*> gameObjects;
    Camera mainCamera;
    GLFWwindow* window;
};

#endif