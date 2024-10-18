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


#pragma region Old Vertex Data (commented out)
    //vertexData = {
    //    // Position        // RGB Color
    //    50.0f,  50.0f, 0.0f,     1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // top-right
    //    50.0f, -50.0f, 0.0f,     0.0f, 1.0f, 0.0f,  1.0f ,0.0f,// bottom-right
    //    -50.0f, -50.0f, 0.0f,    0.0f, 0.0f, 1.0f,  0.0f ,0.0f,// bottom-left
    //    -50.0f,  50.0f, 0.0f,    1.0f, 1.0f, 1.0f,  0.0f, 1.0f // top-left
    //};
#pragma endregion 

        vertexData = {
            /* Position */ /* Normals */ /* Texture Coords */
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f


    };


    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);


#pragma region IMPORTANT ALL INDEX DATA HAS BEEN COMMENTED OUT
    //indexData = { 2, 0, 3, 2, 1, 0 };

    //glGenBuffers(1, &indexBuffer);
    //glBindBuffer(GL_ARRAY_BUFFER, indexBuffer);
    //glBufferData(GL_ARRAY_BUFFER, indexData.size() * sizeof(float), indexData.data(), GL_STATIC_DRAW);
#pragma endregion 
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



void Mesh::BindAttributes()
{
 #pragma region vertices attribute buffer
    glEnableVertexAttribArray(shader->GetAttrVertices());
    glVertexAttribPointer(shader->GetAttrVertices(),
        3, GL_FLOAT, GL_FALSE,    // size, type normalized?,
        8 * sizeof(float),        // stride (8 floats per vertex definition)
        (void*)0                  // array buffer offset
    );
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); // Bind the vertex buffer
 #pragma endregion

#pragma region normals attribute buffer
    glEnableVertexAttribArray(shader->GetAttrNormals());
    glVertexAttribPointer(shader->GetAttrNormals(),
        3, GL_FLOAT, GL_FALSE,
        8 * sizeof(float), // stride (8 floats per vertex definition)
        (void*)(3 * sizeof(float))
    );
#pragma endregion

#pragma region texCoords attribute buffer
    glEnableVertexAttribArray(shader->GetAttrTexCoords());
    glVertexAttribPointer(shader->GetAttrTexCoords(),
        2, GL_FLOAT, GL_FALSE,
        8 * sizeof(float), // stride (8 floats per vertex definition)
        (void*)(6 * sizeof(float))
    );
#pragma endregion

#pragma region Index Buffer (Commented out)
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer); // Bind the index buffer
#pragma endregion

#pragma region Set Texture 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.GetTexture());
    glUniform1i(shader->GetSampler1(), 0);
#pragma endregion

#pragma region Set Texture 1
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2.GetTexture());
    glUniform1i(shader->GetSampler2(), 1);
#pragma endregion
}

void Mesh::CalculateTransform()
{
    // Remember Matrix math is right to left so you read it bottom up
    // If we write this we get: world = T * R(Yaw, Pitch, Roll) * S
    world = glm::translate(glm::mat4(1.0f), position);
    world = glm::rotate(world, rotation.y, glm::vec3(0, 1, 0)); // Yaw
    world = glm::rotate(world, rotation.x, glm::vec3(1, 0, 0)); // Pitch
    world = glm::rotate(world, rotation.z, glm::vec3(0, 0, 1)); // Roll
    world = glm::scale(world, scale);
}

void Mesh::SetShaderVariables(glm::mat4 _pv)
{
    shader->SetMat4("World", world);
    shader->SetVec3("AmbientLight", { 0.1f, 0.1f, 0.1f });
    shader->SetVec3("DiffuseColor", { 1.0f, 1.0f, 1.0f });
    shader->SetFloat("SpecularStrength", 10.0f);
    shader->SetVec3("SpecularColor", { 3.0f, 0.0f, 0.0f });
    shader->SetVec3("LightPosition", lightPosition);
    shader->SetVec3("LightColor", lightColor);
    shader->SetMat4("WVP", _pv * world);
    shader->SetVec3("CameraPosition", cameraPosition);
}

void Mesh::Render(glm::mat4 _pv)
{
    glUseProgram(shader->GetProgramID()); // Use our shader

    rotation.y += 0.005f;

    CalculateTransform();
    SetShaderVariables(_pv);
    BindAttributes();

    glDrawArrays(GL_TRIANGLES, 0, vertexData.size() / 8);
    glDisableVertexAttribArray(shader->GetAttrVertices());
    glDisableVertexAttribArray(shader->GetAttrNormals());
    glDisableVertexAttribArray(shader->GetAttrTexCoords());
}