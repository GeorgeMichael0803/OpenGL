#ifndef NPC_H
#define NPC_H

#include "StandardIncludes.h"
#include "Shader.h"

class NPC {
public:
    NPC();  
    void Create(Shader* shader);
    void Render(glm::mat4 wvp, glm::vec3 playerPosition);  
    void Cleanup();

    glm::vec3 GetPosition() const { return position; }
    void SetPosition(const glm::vec3& newPosition) { position = newPosition; }
    void SetTagged(bool tagged) { this->tagged = tagged; }  // method to tag NPC

private:
    GLuint vertexBuffer = 0;
    GLuint indexBuffer = 0;
    Shader* shader = nullptr;
    std::vector<GLfloat> vertexData;  
    std::vector<GLubyte> indexData;    
    glm::vec3 position;  // Position of the NPC
    bool tagged = false;  //  boolean flag for tagged state
};

#endif // NPC_H
