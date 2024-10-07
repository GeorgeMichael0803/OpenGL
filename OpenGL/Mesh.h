#ifndef MESH_H
#define MESH_H

#include "StandardIncludes.h"
#include "Texture.h"
class Shader;

class Mesh
{
public:
    Mesh() = default;
    virtual ~Mesh();

    // Methods
    void Create(Shader* _shader);
    void Cleanup();
    void Render(glm::mat4 wvp);

private:
    Shader* shader = nullptr;
    Texture texture{};
    Texture texture2{};
    GLuint vertexBuffer = 0;
    GLuint indexBuffer = 0;
    std::vector<GLfloat> vertexData;
    std::vector<GLubyte> indexData;
    glm::mat4 world = glm::mat4(1);
    glm::vec3 position;
    glm::vec3 rotation;

    glm::vec2 scroll = glm::vec2(0.0f, 0.0f);  
};

#endif // MESH_H
