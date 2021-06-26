#pragma once
#include <glew.h>

#define MAX_SHADER_TEXT_SIZE 1024

class ShaderProgram
{
public:
	ShaderProgram(const char* vertexShaderName, const char* fragmentShaderName);
	~ShaderProgram();

	void Use(void);

	void SetRotation(GLfloat rotationX, GLfloat rotationY, GLfloat rotationZ);
private:
	GLchar* m_vertexShaderText;
	GLchar* m_fragmentShaderText;

	GLint m_vertexShaderId;
	GLint m_fragmentShaderId;
	GLint m_programId;

	GLint m_rotationLocation;
};

