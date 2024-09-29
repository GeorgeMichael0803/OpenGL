#include "Mesh.h"
#include "Shader.h"

// Removed Constructor

Mesh::~Mesh()
{
    if (vertexBuffer != 0)
    {
        glDeleteBuffers(1, &vertexBuffer);
        vertexBuffer = 0;
    }
    if (indexBuffer != 0)
    {
        glDeleteBuffers(1, &indexBuffer);
        indexBuffer = 0;
    }
}

void Mesh::Create(Shader* _shader)
{
    shader = _shader;

    // Old Vertex Data

#pragma region Icosahedron Vertex Data
// Colors values taken from:
// https://web.archive.org/web/20180301041827/https://prideout.net/archive/colors.php

// Default values to reuse
    float a = 26.0f;
    float b = 42.0f;
    vertexData = {
        /* Position */     /* RGBA Color */
        -a, 0.0f, b,      1.0f,    0.0f,     0.0f,    1.0f, // Red
         a, 0.0f, b,      1.0f,    0.549f,   0.0f,    1.0f, // Orange
        -a, 0.0f, -b,     1.0f,    1.0f,     0.0f,    1.0f, // Yellow
         a, 0.0f, -b,     0.0f,    1.0f,     0.0f,    1.0f, // Green
        0.0f, b, a,       0.0f,    0.0f,     1.0f,    1.0f, // Blue
        0.0f, b, -a,      0.294f,  0.0f,     0.51f,   1.0f, // Indigo
        0.0f, -b, a,      0.502f,  0.0f,     0.502f,  1.0f, // Purple
        0.0f, -b, -a,     1.0f,    1.0f,     1.0f,    1.0f, // White
         b, a, 0.0f,      0.0f,    1.0f,     1.0f,    1.0f, // Cyan
        -b, a, 0.0f,      0.0f,    0.0f,     0.0f,    1.0f, // Black
         b, -a, 0.0f,     0.118f,  0.565f,   1.0f,    1.0f, // Dodger blue
        -b, -a, 0.0f,     0.863f,  0.078f,   0.235f,  1.0f // Crimson
    };
#pragma endregion

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

#pragma region Icosahedron Index Data
    indexData = {
        0, 6, 1, 0, 11, 6, 1, 4, 0, 1, 8, 4,
        1, 10, 8, 2, 5, 3, 2, 9, 5, 2, 11, 9,
        3, 7, 2, 3, 10, 7, 4, 8, 5, 4, 9, 0,
        5, 8, 3, 5, 9, 4, 6, 10, 1, 6, 11, 7,
        7, 10, 6, 7, 11, 2, 8, 10, 3, 9, 11, 0
    };
#pragma endregion
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ARRAY_BUFFER, indexData.size() * sizeof(float), indexData.data(), GL_STATIC_DRAW);

}


void Mesh::Cleanup()
{
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &indexBuffer);
    vertexBuffer = 0;
    indexBuffer = 0;
}


void Mesh::Render(glm::mat4 wvp)
{
    glUseProgram(shader->GetProgramID()); // Use our shader

    world = glm::rotate(world, 0.001f, { 0, 1, 0 });
    wvp *= world;
    glUniformMatrix4fv(shader->GetAttrWVP(), 1, FALSE, &wvp[0][0]);

    // Set the Verticies attribute buffer
    glEnableVertexAttribArray(shader->GetAttrVertices());
    glVertexAttribPointer(
        shader->GetAttrVertices(),  // Match the layout in the shader.
        3,                          // size
        GL_FLOAT,                   // type
        GL_FALSE,                   // normalized?
        7 * sizeof(float),          // stride (7 floats per vertex definition)
        (void*)0                    // array buffer offset
    );

    // Set the Colors attribute buffer
    glEnableVertexAttribArray(shader->GetAttrColors());
    glVertexAttribPointer(
        shader->GetAttrColors(),    // Match the layout in the shader
        4,                          // size
        GL_FLOAT,                   // type
        GL_FALSE,                   // normalized?
        7 * sizeof(float),          // stride (7 floats per vertex definition)
        (void*)(3 * sizeof(float))  // array buffer offset
    );

    // Draw the triangle !
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); // Bind the vertex buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer); // Bind the index buffer
    //glDrawArrays(GL_TRIANGLES, 0, vertexData.size() / 7); // Starting from vertex 0; 3 vertices total -> 1 triangle
    //glDrawArrays(GL_LINES, 0, vertexData.size() / 7); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDrawElements(GL_TRIANGLES, indexData.size(), GL_UNSIGNED_BYTE, (void*)0); // Draw based off index data

    glDisableVertexAttribArray(shader->GetAttrVertices());
    glDisableVertexAttribArray(shader->GetAttrColors());
}

