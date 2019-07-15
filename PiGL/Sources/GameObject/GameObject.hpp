#ifndef IGAMEOBJECT_HPP
#define IGAMEOBJECT_HPP

#include "../Shader/Shader.hpp"
#include "../Mesh/Mesh.hpp"

class IGameObject : public Mesh {
public:
    IGameObject();
    virtual ~IGameObject();

    // This metod was called after when
    // the gameObject is created or instantied
    virtual void OnInit() = 0;

    // This method was called once per frame
    virtual void OnUpdate(const double& deltaTime) = 0;

private:
};

#endif