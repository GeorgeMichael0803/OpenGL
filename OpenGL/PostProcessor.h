#ifndef POSTPROCESSOR_H
#define POSTPROCESSOR_H

#include "StandardIncludes.h"
#include "Texture.h"

class Shader;

class PostProcessor
{
public:
    // Methods
    void Create(Shader* _postShader);
    void Cleanup();
    void Start();
    void End();

private:
    // Methods
    void CreateVertices();
    void CreateBuffers();
    void BindVertices();

private:
    // Members
    GLuint framebuffer = 0;
    GLuint textureColorbuffer = 0;
    GLuint renderBufferObject = 0;
    GLuint vertexBuffer = 0; // GPU vertex buffer
    Shader* postShader = nullptr;
};

#endif // POSTPROCESSOR_H
