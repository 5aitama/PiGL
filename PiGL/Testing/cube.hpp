#ifndef CUBE_HPP
#define CUBE_HPP

#include "../Sources/GameObject/GameObject.hpp"

class Cube : public IGameObject {
public:
    Cube(const int& i);
   ~Cube();

    void OnBeforeInit();
    void OnInit();
    void OnUpdate(const double& deltaTime);
    
    void BeforeDrawMesh(const Camera& camera) const;

    static const SVertex base_vertices[8];
    int i;
};

#endif