#ifndef CAMERA_H
#define CAMERA_H

#include "StandardIncludes.h"

class Camera
{



public:
    // Constructors / Destructors
    Camera() = default;
    Camera(Resolution _resolution);
    Camera(Resolution _resolution, glm::vec3 _position);
    virtual ~Camera() = default;

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
