#include "Mesh.h"
#include "Shader.h"
#include "GameController.h"
#include <OBJ_Loader.h>


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

void Mesh::Create(Shader* _shader, std::string _file)
{
    shader = _shader;

    objl::Loader loader;
    M_ASSERT(loader.LoadFile(_file) == true, "Failed to load mesh"); // Load .obj file

    for (unsigned int i = 0; i < loader.LoadedMeshes.size(); i++)
    {
        objl::Mesh curMesh = loader.LoadedMeshes[i];
        for (unsigned int j = 0; j < curMesh.Vertices.size(); j++)
        {
            vertexData.push_back(curMesh.Vertices[j].Position.X);
            vertexData.push_back(curMesh.Vertices[j].Position.Y);
            vertexData.push_back(curMesh.Vertices[j].Position.Z);
            vertexData.push_back(curMesh.Vertices[j].Normal.X);
            vertexData.push_back(curMesh.Vertices[j].Normal.Y);
            vertexData.push_back(curMesh.Vertices[j].Normal.Z);
            vertexData.push_back(curMesh.Vertices[j].TextureCoordinate.X);
            vertexData.push_back(curMesh.Vertices[j].TextureCoordinate.Y);
        }
    }




#pragma region Old Vertex Data (commented out)
    //vertexData = {
    //    // Position        // RGB Color
    //    50.0f,  50.0f, 0.0f,     1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // top-right
    //    50.0f, -50.0f, 0.0f,     0.0f, 1.0f, 0.0f,  1.0f ,0.0f,// bottom-right
    //    -50.0f, -50.0f, 0.0f,    0.0f, 0.0f, 1.0f,  0.0f ,0.0f,// bottom-left
    //    -50.0f,  50.0f, 0.0f,    1.0f, 1.0f, 1.0f,  0.0f, 1.0f // top-left
    //};
#pragma endregion 


#pragma region Cube with normals and texture coords

    //    vertexData = {
    //        /* Position */ /* Normals */ /* Texture Coords */
    //        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
    //        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
    //        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
    //        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
    //        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
    //        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
    //        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    //        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
    //        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    //        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    //        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    //        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    //        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    //        -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    //        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    //        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    //        -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    //        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    //        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    //        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    //        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    //        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    //        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    //        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    //        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
    //        0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
    //        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    //        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    //        -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    //        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
    //        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    //        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    //        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    //        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    //        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    //        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f


    //};
#pragma endregion

    std::string diffuseMap = loader.LoadedMaterials[0].map_Kd;
    const size_t last_slash_idx = diffuseMap.find_last_of("\\/");
    if (std::string::npos != last_slash_idx)
    {
        diffuseMap.erase(0, last_slash_idx + 1);
    }

    texture = Texture();
    texture.LoadTexture("../Assets/Textures/" + diffuseMap);

    texture2 = Texture();
    texture2.LoadTexture("../Assets/Textures/" + diffuseMap);


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

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); // Bind the vertex buffer

 #pragma region vertices attribute buffer
    glEnableVertexAttribArray(shader->GetAttrVertices());
    glVertexAttribPointer(shader->GetAttrVertices(),
        3, GL_FLOAT, GL_FALSE,    // size, type normalized?,
        8 * sizeof(float),        // stride (8 floats per vertex definition)
        (void*)0                  // array buffer offset
    );
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
    /*glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.GetTexture());
    glUniform1i(shader->GetSampler1(), 0);*/
#pragma endregion

#pragma region Set Texture 1
    /*glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2.GetTexture());
    glUniform1i(shader->GetSampler2(), 1);*/
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
    shader->SetMat4("WVP", _pv * world);
    shader->SetVec3("CameraPosition", cameraPosition);

    // Configure Light
    std::vector<Mesh*>& lights = GameController::GetInstance().GetLights();
    for (int i = 0; i < lights.size(); i++)
    {
        // Configure Light
        shader->SetVec3(Concat("light[", i, "].position").c_str(), lights[i]->GetPosition());
        shader->SetVec3(Concat("light[", i, "].direction").c_str(), lights[i]->GetLightDirection());

        shader->SetVec3(Concat("light[", i, "].ambientColor").c_str(), { 0.1f, 0.1f, 0.1f });
        shader->SetVec3(Concat("light[", i, "].diffuseColor").c_str(), lights[i]->GetColor());
        shader->SetVec3(Concat("light[", i, "].specularColor").c_str(), { 3.0f, 3.0f, 3.0f });

        shader->SetFloat(Concat("light[", i, "].constant").c_str(), 1.0f);
        shader->SetFloat(Concat("light[", i, "].linear").c_str(), 0.09f);
        shader->SetFloat(Concat("light[", i, "].quadratic").c_str(), 0.032f);

        shader->SetFloat(Concat("light[", i, "].coneAngle").c_str(), glm::radians(5.0f));
        shader->SetFloat(Concat("light[", i, "].falloff").c_str(), 200);
    }

    // Configure Material
    shader->SetFloat("material.specularStrength", 8);
    shader->SetTextureSampler("material.diffuseTexture", GL_TEXTURE0, 0, texture.GetTexture());
    shader->SetTextureSampler("material.specularTexture", GL_TEXTURE1, 1, texture2.GetTexture());

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


std::string Mesh::Concat(const std::string& _s1, int _index, const std::string& _s2)
{
    std::string index = std::to_string(_index);
    return (_s1 + index + _s2);
}
