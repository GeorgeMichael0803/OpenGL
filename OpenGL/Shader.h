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

	//Methods 
	void LoadShaders(const char* _vertexFilePath, const char* _fragmentFilePath);
	void Cleanup();
    GLuint GetAttrWVP() { return attrWVP; }

private:
    // Methods
    void CreateShaderProgram(const char* _vertexFilePath, const char* _fragmentFilePath);
    GLuint LoadShaderFile(const char* _filePath, GLenum _type);
    void LoadAttributes();
    void EvaluateShader(int _infoLength, GLuint _id);

    // Members
    GLuint programID = 0;      // ID of our shader program
    GLuint attrVertices = 0;   // Handle for the attribute vertex buffer
    GLuint attrWVP = 0;      
    GLint result = GL_FALSE;
    int infoLogLength = 0;
};

#endif //SHADER_H

