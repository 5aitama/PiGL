#include "Scene.hpp"

Scene::Scene(const WInfos& winfos, GLFWwindow* window) 
    : meshes(), mainCamera(winfos.width, winfos.height, 45.0f, 0.1f, 100.0f), window(window)
{
    mainCamera.Translate(glm::vec3(0.0f, 0.0f, -5.0f));
    mainCamera.Rotate(glm::vec3(0, 0, 0));
}

Scene::~Scene()
    { /* ... */ }

void Scene::AddMesh(Mesh* mesh, std::string name)
{
    if(meshes.find(name) == meshes.end()) 
    {
        meshes.insert(std::pair<std::string, Mesh*>(name, mesh));
    } else {
        std::cout << "Mesh \"" << name << "\" already exist in the scene!" << std::endl;
    }
}

void Scene::OnBeforeRenderGameObjects()
{
    // Front face is counter clock wise
    glFrontFace(GL_CW);
    
    // Cull only the font face
    glCullFace(GL_FRONT);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Get frame buffer size
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    
    // Set the size of screen to the mainCamera
    mainCamera.SetScreenSize(width, height);

    // Set gl view port
    glViewport(0, 0, width, height);

    /* Clear screen with a color... */
    glClearColor(0, 0, 0, 0);
        
    /* Clear sreen */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Scene::OnUpdate(const double& deltaTime) 
{ 
    // Do anything here...
    for(int i = 0; i < 10; i++) {
        std::string name = "cube" + std::to_string(i);
        if(meshes.find(name) != meshes.end()) {
            meshes.at(name)->Rotate(glm::vec3(i / 10.0f, 1.0f, 0.0f) * static_cast<float>(deltaTime));
        }
    }
}

void Scene::OnRenderGameObjects() 
{

    // Draw all mesh
    for(auto it = meshes.begin(); it != meshes.end(); it++) 
    {
        it->second->DrawMesh(mainCamera);
    }

    /* Pool events */
    glfwPollEvents();

    /* Swap buffers */
    glfwSwapBuffers(window);
}