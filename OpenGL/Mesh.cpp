#include "Mesh.h"

Mesh::Mesh()
{
    vertexBuffer = 0;
}

Mesh::~Mesh()
{
}

void Mesh::Create()
{
    m_vertexData = { -1.0f, -1.0f, 0.0f,  1.0f, -1.0f, 0.0f,  0.0f, 1.0f, 0.0f };
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);
}

void Mesh::Cleanup()
{
    glDeleteBuffers(1, &vertexBuffer);
}

void Mesh::Render()
{
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);
}

