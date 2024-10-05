#include "NPC.h"
#include "glm/gtc/random.hpp"
#include "Shader.h"


NPC::NPC() {
    float randomAngle = glm::linearRand(0.0f, 2.0f * glm::pi<float>());
    float randomDistance = glm::linearRand(2.0f, 10.0f);

    position.x = randomDistance * glm::cos(randomAngle);
    position.y = randomDistance * glm::sin(randomAngle);
    position.z = 0.0f;
}

void NPC::Create(Shader* _shader) {
    shader = _shader;

    // Define vertex positions and colors for the NPC triangle (green)
    vertexData = {
        // Position          // Color (Green)
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,  // Bottom left (green)
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,  // Bottom right (green)
         0.0f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f   // Top (green)
    };

    indexData = { 0, 1, 2 };

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(GLubyte), indexData.data(), GL_STATIC_DRAW);
}

void NPC::Render(glm::mat4 wvp, glm::vec3 playerPosition) {

    // Change color to blue if tagged
    if (tagged) {
        vertexData = {
            // Position          // Color (Blue)
            -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f,  
             0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f,  
             0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f   
        };
    
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);
    }

    glm::vec3 direction = glm::normalize(playerPosition - position); // Calculate direction from NPC to player and normalize
    glm::vec3 forward = glm::vec3(0.0f, 1.0f, 0.0f);  //To make the triangle point up initialy 
    float dotProduct = glm::dot(forward, direction); 
    float angle = acos(dotProduct); //to get the angle between the dot product

    // Use cross product to find which direction to rotate, otheriwse the roation is not smooth and sometimes buggy
    glm::vec3 crossProduct = glm::cross(forward, direction);
    if (crossProduct.z < 0) {
        angle = -angle;
    }

    
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f)); // rotation matrix to rotate the NPC towards the player
    glm::mat4 worldMatrix = glm::translate(glm::mat4(1.0f), position) * rotationMatrix;  //  world matrix with the NPC's position and rotation
     

    glUseProgram(shader->GetProgramID());
    glUniformMatrix4fv(shader->GetAttrWVP(), 1, GL_FALSE, &(wvp * worldMatrix)[0][0]);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    
    glEnableVertexAttribArray(shader->GetAttrVertices());
    glVertexAttribPointer(
        shader->GetAttrVertices(),  
        3,                          
        GL_FLOAT,                   
        GL_FALSE,                   
        7 * sizeof(float),          
        (void*)0               
    );

    
    glEnableVertexAttribArray(shader->GetAttrColors());
    glVertexAttribPointer(
        shader->GetAttrColors(),    
        4,                          
        GL_FLOAT,                   
        GL_FALSE,                  
        7 * sizeof(float),          
        (void*)(3 * sizeof(float))  
    );

    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, (void*)0);

    
    glDisableVertexAttribArray(shader->GetAttrVertices());
    glDisableVertexAttribArray(shader->GetAttrColors());
}


void NPC::Cleanup() {
    if (vertexBuffer != 0) {
        glDeleteBuffers(1, &vertexBuffer);
        vertexBuffer = 0;
    }
    if (indexBuffer != 0) {
        glDeleteBuffers(1, &indexBuffer);
        indexBuffer = 0;
    }
}
