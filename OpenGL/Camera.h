#ifndef CAMERA_H
#define CAMERA_H

#include "StandardIncludes.h"

class Camera
{



public:
    // Constructors / Destructors
    Camera() = default;
    Camera(const Resolution& _resolution, const float _near = 0.1f, const float _far = 1000.0f);
    Camera(Resolution _resolution, glm::vec3 _position);
    virtual ~Camera() = default;

    void LookAt(const glm::vec3& _position, const glm::vec3& _lookAt, const glm::vec3& _up)
    {
        view = glm::lookAt(_position, _lookAt, _up);
    }

    // Accessors
    glm::mat4 GetProjection() { return projection; }
    glm::mat4 GetView() { return view; }

    glm::vec3 GetPosition() const { return position; }

private:
    // Members
    glm::mat4 projection = {};
    glm::mat4 view = {};


    glm::vec3 position;
};

#endif // CAMERA_H
