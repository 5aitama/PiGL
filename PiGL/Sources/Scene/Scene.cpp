#include "Scene.hpp"

Scene::Scene(const WInfos& winfos, GLFWwindow* window) 
    : gameObjects(), mainCamera(winfos.width, winfos.height, 45.0f, 0.1f, 100.0f), window(window)
{
    mainCamera.Translate(glm::vec3(0.0f, 0.0f, -5.0f));
    mainCamera.Rotate(glm::vec3(0, 0, 0));
}

Scene::~Scene() {
    for(auto iterator = gameObjects.begin(); iterator != gameObjects.end(); iterator++) {
        delete iterator->second;
    }
 }

void Scene::AddGameObject(IGameObject* gameObject, const std::string& name) {
    if(gameObjects.find(name) == gameObjects.end()) {
        gameObject->OnBeforeInit();
        gameObject->OnInit();
        gameObjects.insert(std::pair<std::string, IGameObject*>(name, gameObject));
    } else {
        std::cout << "GameObject \"" << name << "\" already exist in the scene!" << std::endl;
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
    for(auto iterator = gameObjects.begin(); iterator != gameObjects.end(); iterator++) {
        iterator->second->OnUpdate(deltaTime);
    }
}

void Scene::OnRenderGameObjects() 
{

    // Draw all mesh
    for(auto iterator = gameObjects.begin(); iterator != gameObjects.end(); iterator++) {
        iterator->second->BeforeDrawMesh(mainCamera);
        iterator->second->DrawMesh(mainCamera);
    }

    /* Pool events */
    glfwPollEvents();

    /* Swap buffers */
    glfwSwapBuffers(window);
}