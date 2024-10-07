#ifndef SHADER_H
#define SHADER_H

#include "..\OpenGL\StandardIncludes.h"

class Shader
{
public:
	//Constructors /Destructors 
	Shader() = default; 
	virtual ~Shader();


	//Accessors 
	GLuint GetProgramID() { return programID; }
	GLuint GetAttrVertices() { return attrVertices; }
    GLuint GetAttrColors() { return attrColors; }
    GLuint GetAttrTexCoords() { return attrTexCoords; }
    GLuint GetSampler1() { return sampler1; }
    GLuint GetSampler2() { return sampler2; }
    GLuint GetAttrWVP() { return attrWVP; }

	//Methods 
	void LoadShaders(const char* _vertexFilePath, const char* _fragmentFilePath);
	void Cleanup();
    

private:
    // Methods
    void CreateShaderProgram(const char* _vertexFilePath, const char* _fragmentFilePath);
    GLuint LoadShaderFile(const char* _filePath, GLenum _type);
    void LoadAttributes();
    void EvaluateShader(int _infoLength, GLuint _id);

    // Members
    GLuint programID = 0;      // ID of our shader program
    GLuint attrVertices = 0;   // Handle for the attribute vertex buffer
    GLuint attrColors = 0;   // Handle for the attribute Color
    GLuint attrTexCoords = 0; // Handle for the attribute Tex Coords
    GLuint sampler1 = 0; // Handle for the attribute sampler 1
    GLuint sampler2 = 0;  // Handle for the second texture sampler
    GLuint attrWVP = 0;      
    GLint result = GL_FALSE;
    int infoLogLength = 0;
};

#endif //SHADER_H

