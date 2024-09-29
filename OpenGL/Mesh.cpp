#include "Mesh.h"
#include "Shader.h"

// Removed Constructor

Mesh::~Mesh()
{
    if (vertexBuffer != 0)
    {
        glDeleteBuffers(1, &vertexBuffer);
    }
}

void Mesh::Create(Shader* _shader)
{
    shader = _shader;

    vertexData = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f,  0.0f , 1.0f , 0.0f };
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);
}


void Mesh::Cleanup()
{
    glDeleteBuffers(1, &vertexBuffer);
    vertexBuffer = 0;
}

void Mesh::Render(glm::mat4 wvp)
{
    glUseProgram(shader->GetProgramID()); // Use our shader

    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(shader->GetAttrVertices());
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    wvp *= world;
    glUniformMatrix4fv(shader->GetAttrWVP(), 1, FALSE, &wvp[0][0]);
    glVertexAttribPointer(
        shader->GetAttrVertices(),  // Match the layout in the shader.
        3,                          // size
        GL_FLOAT,                   // type
        GL_FALSE,                   // normalized?
        0,                          // stride
        (void*)0                    // array buffer offset
    );

    // Draw the triangle!
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(shader->GetAttrVertices());
}

