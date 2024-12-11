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
    textureDiffuse.Cleanup();
    textureSpecular.Cleanup();
}




void Mesh::LoadASE(std::string& _file)
{
    ASEReader reader;
    reader.ParseASEFile(_file.c_str());
    ASEReader::MeshInfo& m = reader.GeoObjects[0]->MeshI;
    ASEReader::Material* mat = reader.Materials[reader.GeoObjects[0]->MaterialID];

    std::vector<objl::Vector3> tangents;
    std::vector<objl::Vector3> bitangents;
    std::vector<objl::Vertex> triangle;
    objl::Vector3 tangent;
    objl::Vector3 bitangent;
    int vCount = 0;

    for (int count = 0; count < m.NumFaces; count++)
    {
        glm::vec3 tF = m.TexFaces[count];
        glm::vec3 f = m.Faces[count];
        triangle.clear();

        objl::Vertex vert = objl::Vertex();
        vert.Position = objl::Vector3(m.Vertices[(int)f.x].x, m.Vertices[(int)f.x].y, m.Vertices[(int)f.x].z);
        vert.Normal = objl::Vector3(m.VertexNormals[vCount].x, m.VertexNormals[vCount].y, m.VertexNormals[vCount].z);
        vert.TextureCoordinate = objl::Vector2(m.TexVertices[(int)tF.x].x, m.TexVertices[(int)tF.x].y);
        triangle.push_back(vert);

        vCount++;


        vert = objl::Vertex();
        vert.Position = objl::Vector3(m.Vertices[(int)f.y].x, m.Vertices[(int)f.y].y, m.Vertices[(int)f.y].z);
        vert.Normal = objl::Vector3(m.VertexNormals[vCount].x, m.VertexNormals[vCount].y, m.VertexNormals[vCount].z);
        vert.TextureCoordinate = objl::Vector2(m.TexVertices[(int)tF.y].x, m.TexVertices[(int)tF.y].y);
        triangle.push_back(vert);
        vCount++;

        vert = objl::Vertex();
        vert.Position = objl::Vector3(m.Vertices[(int)f.z].x, m.Vertices[(int)f.z].y, m.Vertices[(int)f.z].z);
        vert.Normal = objl::Vector3(m.VertexNormals[vCount].x, m.VertexNormals[vCount].y, m.VertexNormals[vCount].z);
        vert.TextureCoordinate = objl::Vector2(m.TexVertices[(int)tF.z].x, m.TexVertices[(int)tF.z].y);
        triangle.push_back(vert);
        vCount++;

        CalculateTangents(triangle, tangent, bitangent);
        tangents.push_back(tangent);
        bitangents.push_back(bitangent);


        for (int c = 0; c < 3; c++)
        {
            vertexData.push_back(triangle[c].Position.X);
            vertexData.push_back(triangle[c].Position.Y);
            vertexData.push_back(triangle[c].Position.Z);
            vertexData.push_back(triangle[c].Normal.X);
            vertexData.push_back(triangle[c].Normal.Y);
            vertexData.push_back(triangle[c].Normal.Z);
            vertexData.push_back(triangle[c].TextureCoordinate.X);
            vertexData.push_back(triangle[c].TextureCoordinate.Y);

            int index = (vCount / 3) - 1;
            vertexData.push_back(tangents[index].X);
            vertexData.push_back(tangents[index].Y);
            vertexData.push_back(tangents[index].Z);
            vertexData.push_back(bitangents[index].X);
            vertexData.push_back(bitangents[index].Y);
            vertexData.push_back(bitangents[index].Z);
        }

    }


    textureDiffuse = Texture();
    if (mat->Maps[0].Name == "DIFFUSE")
    {
        textureDiffuse.LoadTexture("../Assets/Textures/" + RemoveFolder(mat->Maps[0].TextureFileName));
    }

    textureSpecular = Texture();
    if (mat->Maps[1].Name == "SPECULAR")
    {
        textureSpecular.LoadTexture("../Assets/Textures/" + RemoveFolder(mat->Maps[1].TextureFileName));
    }

    textureNormal = Texture();
    if (mat->Maps[1].Name == "BUMP")
    {
        textureNormal.LoadTexture("../Assets/Textures/" + RemoveFolder(mat->Maps[1].TextureFileName));
        enableNormalMaps = true;
    }
    else if (mat->Maps[2].Name == "BUMP")
    {
        textureNormal.LoadTexture("../Assets/Textures/" + RemoveFolder(mat->Maps[2].TextureFileName));
        enableNormalMaps = true;
    }

}

void Mesh::LoadOBJ(std::string& _file)
{
    objl::Loader loader;
    M_ASSERT(loader.LoadFile(_file) == true, "Failed to load mesh"); // Load .obj file

    for (unsigned int i = 0; i < loader.LoadedMeshes.size(); i++)
    {
        objl::Mesh curMesh = loader.LoadedMeshes[i];
        std::vector<objl::Vector3> tangents;
        std::vector<objl::Vector3> bitangents;
        std::vector<objl::Vertex> triangle;
        objl::Vector3 tangent;
        objl::Vector3 bitangent;
        for (unsigned int j = 0; j < curMesh.Vertices.size(); j += 3)
        {
            triangle.clear();
            triangle.push_back(curMesh.Vertices[j]);
            triangle.push_back(curMesh.Vertices[j + 1]);
            triangle.push_back(curMesh.Vertices[j + 2]);
            CalculateTangents(triangle, tangent, bitangent);
            tangents.push_back(tangent);
            bitangents.push_back(bitangent);
        }

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

            if (loader.LoadedMaterials[0].map_bump != "")
            {
                int index = j / 3;
                vertexData.push_back(tangents[index].X);
                vertexData.push_back(tangents[index].Y);
                vertexData.push_back(tangents[index].Z);
                vertexData.push_back(bitangents[index].X);
                vertexData.push_back(bitangents[index].Y);
                vertexData.push_back(bitangents[index].Z);
            }
        }
    }

    textureDiffuse = Texture();
    if (loader.LoadedMaterials[0].map_Kd != "")
    {
        textureDiffuse.LoadTexture("../Assets/Textures/" + RemoveFolder(loader.LoadedMaterials[0].map_Kd));
    }
    else // Backup just for safety
    {
        textureDiffuse.LoadTexture("../Assets/Textures/Pattern.png");
    }

    textureSpecular = Texture();
    if (loader.LoadedMaterials[0].map_Ks != "")
    {
        textureSpecular.LoadTexture("../Assets/Textures/" + RemoveFolder(loader.LoadedMaterials[0].map_Ks));
    }

    textureNormal = Texture();
    if (loader.LoadedMaterials[0].map_bump != "")
    {
        enableNormalMaps = true;
        textureNormal.LoadTexture("../Assets/Textures/" + RemoveFolder(loader.LoadedMaterials[0].map_bump));
    }
}




bool Mesh::EndsWith(const std::string& _str, const std::string& _suffix)
{
    return _str.size() >= _suffix.size() && 0 == _str.compare(_str.size() - _suffix.size(), _suffix.size(), _suffix);
}


void Mesh::Create(Shader* _shader, std::string _file, int _instanceCount)

{
    shader = _shader;

    instanceCount = _instanceCount;
    enableInstancing = instanceCount > 1 ? true : false;


    if (EndsWith(_file, "ase"))
    {
        LoadASE(_file);
    }
    else
    {
        LoadOBJ(_file);
    }

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    if (enableInstancing)
    {
        glGenBuffers(1, &instanceBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, instanceBuffer);

        srand(glfwGetTime()); // Initialize random seed
        for (unsigned int i = 0; i < instanceCount; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(-20 + rand() % 40, -10 + rand() % 20, -10 + rand() % 20));
            // model = glm::mat4(1.0f);
            for (int x = 0; x < 4; x++)
            {
                for (int y = 0; y < 4; y++)
                {
                    instanceData.push_back(model[x][y]);
                }
            }
        }

        glBufferData(GL_ARRAY_BUFFER, instanceCount * sizeof(glm::mat4), instanceData.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }


    vertexStride = 8;
    if (enableNormalMaps)
    {
        vertexStride += 6;
    }



#pragma region IMPORTANT ALL INDEX DATA HAS BEEN COMMENTED OUT
    //indexData = { 2, 0, 3, 2, 1, 0 };

    //glGenBuffers(1, &indexBuffer);
    //glBindBuffer(GL_ARRAY_BUFFER, indexBuffer);
    //glBufferData(GL_ARRAY_BUFFER, indexData.size() * sizeof(float), indexData.data(), GL_STATIC_DRAW);
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

}



void Mesh::Cleanup()
{
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &indexBuffer);
    textureDiffuse.Cleanup();
    textureSpecular.Cleanup();
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
        vertexStride * sizeof(float),        // stride (8 floats per vertex definition)
        (void*)0                  // array buffer offset
    );
 #pragma endregion

#pragma region normals attribute buffer
    glEnableVertexAttribArray(shader->GetAttrNormals());
    glVertexAttribPointer(shader->GetAttrNormals(),
        3, GL_FLOAT, GL_FALSE,
        vertexStride * sizeof(float), // stride (8 floats per vertex definition)
        (void*)(3 * sizeof(float))
    );
#pragma endregion

#pragma region texCoords attribute buffer
    glEnableVertexAttribArray(shader->GetAttrTexCoords());
    glVertexAttribPointer(shader->GetAttrTexCoords(),
        2, GL_FLOAT, GL_FALSE,
        vertexStride * sizeof(float), // stride (8 floats per vertex definition)
        (void*)(6 * sizeof(float))
    );
#pragma endregion

#pragma region BindNormalMapData
    if (enableNormalMaps)
    {
        // 4th attribute buffer : tangent
        glEnableVertexAttribArray(shader->GetAttrTangents());
        glVertexAttribPointer(shader->GetAttrTangents(), // The attribute we want to configure
            3, GL_FLOAT, GL_FALSE,   // size, type, normalized?,
            vertexStride * sizeof(float), // stride floats per vertex definition
            (void*)(8 * sizeof(float))); // array buffer offset

        // 5th attribute buffer : bitangent
        glEnableVertexAttribArray(shader->GetAttrBitangents());
        glVertexAttribPointer(shader->GetAttrBitangents(), // The attribute we want to configure
            3, GL_FLOAT, GL_FALSE,   // size, type, normalized?,
            vertexStride * sizeof(float), // stride floats per vertex definition
            (void*)(11 * sizeof(float))); // array buffer offset
    }
#pragma endregion

#pragma region BindInstancingData
    if (enableInstancing)
    {
        glBindBuffer(GL_ARRAY_BUFFER, instanceBuffer); // Bind the vertex buffer

        // Set attribute pointers for instance matrix (4 times vec4)
        glEnableVertexAttribArray(shader->GetAttrInstanceMatrix());
        glVertexAttribPointer(shader->GetAttrInstanceMatrix(),
            4, GL_FLOAT, GL_FALSE, // size (4 components), type, normalized?
            sizeof(glm::mat4), // stride
            (void*)0); // instance buffer offset

        glEnableVertexAttribArray(shader->GetAttrInstanceMatrix() + 1);
        glVertexAttribPointer(shader->GetAttrInstanceMatrix() + 1,
            4, GL_FLOAT, GL_FALSE, // size (4 components), type, normalized?
            sizeof(glm::mat4), // stride
            (void*)(sizeof(glm::vec4))); // instance buffer offset

        glEnableVertexAttribArray(shader->GetAttrInstanceMatrix() + 2);
        glVertexAttribPointer(shader->GetAttrInstanceMatrix() + 2,
            4, GL_FLOAT, GL_FALSE, // size (4 components), type, normalized?
            sizeof(glm::mat4), // stride
            (void*)(2 * sizeof(glm::vec4))); // instance buffer offset

        glEnableVertexAttribArray(shader->GetAttrInstanceMatrix() + 3);
        glVertexAttribPointer(shader->GetAttrInstanceMatrix() + 3,
            4, GL_FLOAT, GL_FALSE, // size (4 components), type, normalized?
            sizeof(glm::mat4), // stride
            (void*)(3 * sizeof(glm::vec4))); // instance buffer offset

        glVertexAttribDivisor(shader->GetAttrInstanceMatrix(), 1);
        glVertexAttribDivisor(shader->GetAttrInstanceMatrix() + 1, 1);
        glVertexAttribDivisor(shader->GetAttrInstanceMatrix() + 2, 1);
        glVertexAttribDivisor(shader->GetAttrInstanceMatrix() + 3, 1);
    }
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
    shader->SetInt("EnableNormalMaps", enableNormalMaps);
    shader->SetInt("EnableInstancing", enableInstancing);


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
    shader->SetTextureSampler("material.diffuseTexture", GL_TEXTURE0, 0, textureDiffuse.GetTexture());
    shader->SetTextureSampler("material.specularTexture", GL_TEXTURE1, 1, textureSpecular.GetTexture());
    shader->SetTextureSampler("material.normalTexture", GL_TEXTURE2, 2, textureNormal.GetTexture());
}

void Mesh::Render(glm::mat4 _pv)
{
    glUseProgram(shader->GetProgramID()); // Use our shader

    CalculateTransform();
    SetShaderVariables(_pv);
    BindAttributes();

    if (enableInstancing)
    {
        glDrawArraysInstanced(GL_TRIANGLES, 0, vertexData.size() / vertexStride, instanceCount);
    }
    else
    {
        glDrawArrays(GL_TRIANGLES, 0, vertexData.size() / vertexStride);
    }

    glDisableVertexAttribArray(shader->GetAttrVertices());
    glDisableVertexAttribArray(shader->GetAttrNormals());
    glDisableVertexAttribArray(shader->GetAttrTexCoords());
    if (enableNormalMaps)
    {
        glDisableVertexAttribArray(shader->GetAttrTangents());
        glDisableVertexAttribArray(shader->GetAttrBitangents());
    }

    if (enableInstancing)
    {
        glDisableVertexAttribArray(shader->GetAttrInstanceMatrix());
        glDisableVertexAttribArray(shader->GetAttrInstanceMatrix() + 1);
        glDisableVertexAttribArray(shader->GetAttrInstanceMatrix() + 2);
        glDisableVertexAttribArray(shader->GetAttrInstanceMatrix() + 3);
    }

}


std::string Mesh::Concat(const std::string& _s1, int _index, const std::string& _s2)
{
    std::string index = std::to_string(_index);
    return (_s1 + index + _s2);
}


std::string Mesh::RemoveFolder(std::string& _map)
{
    const size_t last_slash_idx = _map.find_last_of("\\/");
    if (std::string::npos != last_slash_idx)
    {
        _map.erase(0, last_slash_idx + 1);
    }
    return _map;
}


void Mesh::CalculateTangents(std::vector<objl::Vertex> _vertices, objl::Vector3& _tangent, objl::Vector3& _bitangent)
{
    // calculate tangent/bitangent vectors of both triangles
    objl::Vector3 edge1 = _vertices[1].Position - _vertices[0].Position;
    objl::Vector3 edge2 = _vertices[2].Position - _vertices[0].Position;
    objl::Vector2 deltaUV1 = _vertices[1].TextureCoordinate - _vertices[0].TextureCoordinate;
    objl::Vector2 deltaUV2 = _vertices[2].TextureCoordinate - _vertices[0].TextureCoordinate;

    float f = 1.0f / (deltaUV1.X * deltaUV2.Y - deltaUV2.X * deltaUV1.Y);

    _tangent.X = f * (deltaUV2.Y * edge1.X - deltaUV1.Y * edge2.X);
    _tangent.Y = f * (deltaUV2.Y * edge1.Y - deltaUV1.Y * edge2.Y);
    _tangent.Z = f * (deltaUV2.Y * edge1.Z - deltaUV1.Y * edge2.Z);

    _bitangent.X = f * (-deltaUV2.X * edge1.X + deltaUV1.X * edge2.X);
    _bitangent.Y = f * (-deltaUV2.X * edge1.Y + deltaUV1.X * edge2.Y);
    _bitangent.Z = f * (-deltaUV2.X * edge1.Z + deltaUV1.X * edge2.Z);
}






        


