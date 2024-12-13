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




    void SetWireframe(bool enabled);
    void SetFrequency(float freq);
    void SetAmplitude(float amp);
    void SetTintBlue(bool enabled);
    void SetTime(float time);

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




    bool wireframe = false;
    bool tintBlue = false;
    float frequency = 1.0f;
    float amplitude = 0.1f;
};

#endif // POSTPROCESSOR_H
