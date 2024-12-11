#ifndef FONT_H
#define FONT_H

#include "StandardIncludes.h"

class Shader;

struct Character
{
    unsigned int textureID;  // ID handle of the glyph texture
    glm::ivec2 size;         // Size of glyph
    glm::ivec2 bearing;      // Offset from baseline to left/top of glyph
    unsigned int advance;    // Offset to advance to next glyph
};

class Font
{
public:
    // Methods
    void Create(Shader* _shader, std::string _name, FT_UInt _size);
    void Cleanup();
    void RenderText(std::string _text, float _x, float _y, float _scale, glm::vec3 _color);

private:
    // Members
    Shader* shader = nullptr;
    FT_Library library = nullptr;
    FT_Face face = nullptr;
    std::map<char, Character> characters;
    GLuint vertexBuffer = 0;
    glm::mat4 orthoProj = {};

    // Methods
    void Initialize(std::string _fileName, FT_UInt _size);
    void CreateCharacters();
    void AllocateBuffers();
};

#endif // FONT_H
