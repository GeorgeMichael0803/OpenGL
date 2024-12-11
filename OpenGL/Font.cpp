#include "Font.h"
#include "Shader.h"
#include "WindowController.h"

void Font::Create(Shader* _shader, std::string _name, FT_UInt _size)
{
    shader = _shader;

    AllocateBuffers();
    Initialize(_name, _size);
}

void Font::AllocateBuffers()
{
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
}

void Font::Initialize(std::string _fileName, FT_UInt _size)
{
    Resolution r = WindowController::GetInstance().GetResolution();
    orthoProj = glm::ortho(0.0f, (float)r.width, 0.0f, (float)r.height);

    // Initialize the library and font face
    M_ASSERT(FT_Init_FreeType(&library) == false, "Could not init FreeType Library");
    M_ASSERT(FT_New_Face(library, _fileName.c_str(), 0, &face) == false, "Failed to load font");

    // Set font height to 48 (0 to auto-calculate width)
    M_ASSERT(FT_Set_Pixel_Sizes(face, 0, _size) == false, "Failed to set character size");

    // Disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    CreateCharacters();

    // Free library resources
    FT_Done_Face(face);
    FT_Done_FreeType(library);
}

void Font::CreateCharacters()
{
    // Load First 128 character glyphs into character textures
    for (unsigned char c = 0; c < 128; c++)
    {
        // Load character glyph
        M_ASSERT(FT_Load_Char(face, c, FT_LOAD_RENDER) == false, "Failed to load Glyph");

        // Generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows,
            0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Now store character for later use
        Character character = { texture,
                                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                                (unsigned int)face->glyph->advance.x };
        characters.insert(std::pair<char, Character>(c, character));
    }
}

void Font::RenderText(std::string _text, float _x, float _y, float _scale, glm::vec3 _color)
{
    _y = WindowController::GetInstance().GetResolution().height - _y;
    glUseProgram(shader->GetProgramID()); // Use our shader

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); // Bind the vertex buffer

    shader->SetVec3("textColor", _color);
    glUniformMatrix4fv(glGetUniformLocation(shader->GetProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(orthoProj));

    // Iterate through all characters
    std::string::const_iterator c;
    for (c = _text.begin(); c != _text.end(); c++)
    {
        Character ch = characters[*c];
        float xpos = _x + ch.bearing.x * _scale;
        float ypos = _y - (ch.size.y - ch.bearing.y) * _scale;
        float w = ch.size.x * _scale;
        float h = ch.size.y * _scale;

        // Update vertex buffer for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,     0.0f, 0.0f },
            { xpos,     ypos,         0.0f, 1.0f },
            { xpos + w, ypos,         1.0f, 1.0f },

            { xpos,     ypos + h,     0.0f, 0.0f },
            { xpos + w, ypos,         1.0f, 1.0f },
            { xpos + w, ypos + h,     1.0f, 0.0f }
        };

        // Render glyph texture over quad
        shader->SetTextureSampler("material.diffuseTexture", GL_TEXTURE0, 0, ch.textureID);

        // Update content of vertex buffer memory
        glEnableVertexAttribArray(shader->GetAttrVertices());
        glVertexAttribPointer(shader->GetAttrVertices(), 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        _x += (ch.advance >> 6) * _scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))

        
    }

    glDisableVertexAttribArray(shader->GetAttrVertices());
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Font::Cleanup()
{
    glDeleteBuffers(1, &vertexBuffer);
    for (auto it : characters)
    {
        glGenTextures(1, &(it.second.textureID));
    }
}
