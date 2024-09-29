#include "Camera.h"

Camera::Camera(const Resolution& _resolution, const float _near, const float _far)
{
    projection = glm::perspective(glm::radians(45.0f),
        (float)_resolution.width / (float)_resolution.height,
        _near,
        _far);

    view = glm::lookAt(
        glm::vec3(1, 0, 0), // Default is at 1, 0, 0 in World Space
        glm::vec3(0, 0, 0), // and looks at the origin
        glm::vec3(0, 1, 0)  // Head is up (set to 0, -1, 0 to look upside-down)
    );
}



Camera::Camera(Resolution _resolution, glm::vec3 _position)
{
    projection = glm::perspective(glm::radians(_resolution.fov), 
        (float)_resolution.width / (float)_resolution.height, 
        0.1f, 
        1000.0f);

    view = glm::lookAt(
        _position,          // Camera position in world space
        glm::vec3(0, 0, 0), // Look at the origin
        glm::vec3(0, 1, 0)  // Head is up (set to 0, -1, 0 to look upside-down)
    );

    position = _position;
    
}

