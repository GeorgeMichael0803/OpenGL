#include "Mesh.h"
#include "Shader.h"

Mesh::~Mesh() {
    if (vertexBuffer != 0) {
        glDeleteBuffers(1, &vertexBuffer);
        vertexBuffer = 0;
    }
    if (indexBuffer != 0) {
        glDeleteBuffers(1, &indexBuffer);
        indexBuffer = 0;
    }
}

void Mesh::Create(Shader* _shader) {
    shader = _shader;

    
    vertexData = {
        // Position         // Color (Red)
        -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f,  
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f, 
         0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f   
    };

    indexData = { 0, 1, 2 };

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(GLubyte), indexData.data(), GL_STATIC_DRAW);
}

void Mesh::Render(glm::mat4 wvp)
{
    glUseProgram(shader->GetProgramID()); 

    
    glUniformMatrix4fv(shader->GetAttrWVP(), 1, GL_FALSE, &wvp[0][0]);

    
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    // Set the vertex attribute pointers for position and color
    glEnableVertexAttribArray(shader->GetAttrVertices());
    glVertexAttribPointer(
        shader->GetAttrVertices(),  // Attribute layout for position
        3,                          // size (3 floats for position)
        GL_FLOAT,                   // type of data
        GL_FALSE,                   // normalized?
        7 * sizeof(float),          // stride (position + color)
        (void*)0                    // offset
    );

    // Set the color attribute buffer
    glEnableVertexAttribArray(shader->GetAttrColors());
    glVertexAttribPointer(
        shader->GetAttrColors(),    // Attribute layout for color
        4,                          // size (4 floats for color)
        GL_FLOAT,                   // type of data
        GL_FALSE,                   // normalized?
        7 * sizeof(float),          // stride (position + color)
        (void*)(3 * sizeof(float))  // color starts after position
    );

    // Bind the index buffer for the player
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glDrawElements(GL_TRIANGLES, indexData.size(), GL_UNSIGNED_BYTE, (void*)0);

    // Clean up the state after rendering (to avoid it affecting subsequent renders)
    glDisableVertexAttribArray(shader->GetAttrVertices());
    glDisableVertexAttribArray(shader->GetAttrColors());
}

void Mesh::Cleanup() {
    if (vertexBuffer != 0) {
        glDeleteBuffers(1, &vertexBuffer);
        vertexBuffer = 0;
    }
    if (indexBuffer != 0) {
        glDeleteBuffers(1, &indexBuffer);
        indexBuffer = 0;
    }
}
