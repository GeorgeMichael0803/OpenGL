#include "Mesh.h"
#include "Shader.h"

// Removed Constructor

//#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>


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
    texture.Cleanup();
    texture2.Cleanup();
}

void Mesh::Create(Shader* _shader)
{
    shader = _shader;
    texture = Texture();
    texture.LoadTexture("../Assets/Textures/Tacos.jpg");

    texture2 = Texture();
    texture2.LoadTexture("../Assets/Textures/Pattern.png");


    // Old Vertex Data

#pragma region Icosahedron Vertex Data
// Colors values taken from:
// https://web.archive.org/web/20180301041827/https://prideout.net/archive/colors.php

// Default values to reuse
    //float a = 26.0f;
    //float b = 42.0f;
    //vertexData = {
    //    /* Position */     /* RGBA Color */
    //    -a, 0.0f, b,      1.0f,    0.0f,     0.0f,    1.0f, // Red
    //     a, 0.0f, b,      1.0f,    0.549f,   0.0f,    1.0f, // Orange
    //    -a, 0.0f, -b,     1.0f,    1.0f,     0.0f,    1.0f, // Yellow
    //     a, 0.0f, -b,     0.0f,    1.0f,     0.0f,    1.0f, // Green
    //    0.0f, b, a,       0.0f,    0.0f,     1.0f,    1.0f, // Blue
    //    0.0f, b, -a,      0.294f,  0.0f,     0.51f,   1.0f, // Indigo
    //    0.0f, -b, a,      0.502f,  0.0f,     0.502f,  1.0f, // Purple
    //    0.0f, -b, -a,     1.0f,    1.0f,     1.0f,    1.0f, // White
    //     b, a, 0.0f,      0.0f,    1.0f,     1.0f,    1.0f, // Cyan
    //    -b, a, 0.0f,      0.0f,    0.0f,     0.0f,    1.0f, // Black
    //     b, -a, 0.0f,     0.118f,  0.565f,   1.0f,    1.0f, // Dodger blue
    //    -b, -a, 0.0f,     0.863f,  0.078f,   0.235f,  1.0f // Crimson
    //};
#pragma endregion

#pragma region Icosahedron Index Data
/*indexData = {
    0, 6, 1, 0, 11, 6, 1, 4, 0, 1, 8, 4,
    1, 10, 8, 2, 5, 3, 2, 9, 5, 2, 11, 9,
    3, 7, 2, 3, 10, 7, 4, 8, 5, 4, 9, 0,
    5, 8, 3, 5, 9, 4, 6, 10, 1, 6, 11, 7,
    7, 10, 6, 7, 11, 2, 8, 10, 3, 9, 11, 0
};*/
#pragma endregion



    vertexData = {
        // Position        // RGB Color
        50.0f,  50.0f, 0.0f,     1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // top-right
        50.0f, -50.0f, 0.0f,     0.0f, 1.0f, 0.0f,  1.0f ,0.0f,// bottom-right
        -50.0f, -50.0f, 0.0f,    0.0f, 0.0f, 1.0f,  0.0f ,0.0f,// bottom-left
        -50.0f,  50.0f, 0.0f,    1.0f, 1.0f, 1.0f,  0.0f, 1.0f // top-left
    };


    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

    indexData = { 2, 0, 3, 2, 1, 0 };




    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ARRAY_BUFFER, indexData.size() * sizeof(float), indexData.data(), GL_STATIC_DRAW);

}


void Mesh::Cleanup()
{
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &indexBuffer);
    texture.Cleanup();
    texture2.Cleanup();
    vertexBuffer = 0;
    indexBuffer = 0;
}


void Mesh::Render(glm::mat4 wvp)
{
    scroll.x += 0.001f; 
    scroll.y += 0.0f;

    glUseProgram(shader->GetProgramID()); // Use the shader

    world = glm::rotate(world, 0.001f, { 0, 1, 0 });
    wvp *= world;
    glUniformMatrix4fv(shader->GetAttrWVP(), 1, GL_FALSE, &wvp[0][0]);

    // Bind the vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    // Set the Vertices attribute buffer
    glEnableVertexAttribArray(shader->GetAttrVertices());
    glVertexAttribPointer(
        shader->GetAttrVertices(),  // Match the layout in the shader
        3,                          // size (3 floats for vertex position)
        GL_FLOAT,                   // type
        GL_FALSE,                   // normalized?
        8 * sizeof(float),          // stride (8 floats per vertex definition)
        (void*)0                    // array buffer offset
    );

    // Set the Colors attribute buffer
    glEnableVertexAttribArray(shader->GetAttrColors());
    glVertexAttribPointer(
        shader->GetAttrColors(),    // Match the layout in the shader
        3,                          // size (3 floats for color)
        GL_FLOAT,                   // type
        GL_FALSE,                   // normalized?
        8 * sizeof(float),          // stride (8 floats per vertex definition)
        (void*)(3 * sizeof(float))  // array buffer offset
    );

    // Set the Texture attribute buffer
    glEnableVertexAttribArray(shader->GetAttrTexCoords());
    glVertexAttribPointer(
        shader->GetAttrTexCoords(),
        2, GL_FLOAT, GL_FALSE,      // size (2 floats for texture coordinates)
        8 * sizeof(float),          // stride (8 floats per vertex definition)
        (void*)(6 * sizeof(float))  // array buffer offset
    );

    // Update the scrollOffset in the shader
    glUniform2fv(shader->GetScroll(), 1, glm::value_ptr(scroll));

    // Bind textures
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.GetTexture());
    glUniform1i(shader->GetSampler1(), 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2.GetTexture());
    glUniform1i(shader->GetSampler2(), 1);

    // Bind index buffer and draw
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glDrawElements(GL_TRIANGLES, indexData.size(), GL_UNSIGNED_BYTE, (void*)0);

    // Disable vertex attribute arrays
    glDisableVertexAttribArray(shader->GetAttrVertices());
    glDisableVertexAttribArray(shader->GetAttrColors());
    glDisableVertexAttribArray(shader->GetAttrTexCoords());
}


