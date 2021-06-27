#pragma once
#include <glew.h>

class ShaderProgram
{
public:
	ShaderProgram(const char* vertexShaderName, const char* fragmentShaderName);
	~ShaderProgram();

	void Use(void);

	void SetRotation(GLfloat rotationX, GLfloat rotationY, GLfloat rotationZ);
	void SetPosition(GLfloat x, GLfloat y, GLfloat z);
	void SetScale(GLfloat x, GLfloat y, GLfloat z);
private:
	GLchar* m_vertexShaderText;
	GLchar* m_fragmentShaderText;

	GLint m_vertexShaderId;
	GLint m_fragmentShaderId;
	GLint m_programId;

	GLint m_rotationLocation;
	GLint m_positionLocation;
	GLint m_scaleLocation;
};

