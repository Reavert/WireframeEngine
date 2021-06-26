#include "ShaderProgram.h"
#include <cstdio>
#include "Utils.h"

ShaderProgram::ShaderProgram(const char* vertexShaderName, const char* fragmentShaderName)
{
	m_vertexShaderText = Utils::LoadFile(vertexShaderName);
	m_fragmentShaderText = Utils::LoadFile(fragmentShaderName);

	m_vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_vertexShaderId, 1, &m_vertexShaderText, NULL);
	glCompileShader(m_vertexShaderId);

	m_fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_fragmentShaderId, 1, &m_fragmentShaderText, NULL);
	glCompileShader(m_fragmentShaderId);
	

	m_programId = glCreateProgram();
	glAttachShader(m_programId, m_vertexShaderId);
	glAttachShader(m_programId, m_fragmentShaderId);

	glLinkProgram(m_programId);

	m_rotationLocation = glGetUniformLocation(m_programId, "rotation");
}

ShaderProgram::~ShaderProgram()
{
	glUseProgram(0);

	glDetachShader(m_programId, m_vertexShaderId);
	glDetachShader(m_programId, m_fragmentShaderId);

	glDeleteShader(m_vertexShaderId);
	glDeleteShader(m_fragmentShaderId);

	glDeleteProgram(m_programId);

	delete m_vertexShaderText;
	delete m_fragmentShaderText;
}

void ShaderProgram::SetRotation(GLfloat rotationX, GLfloat rotationY, GLfloat rotationZ)
{
	glProgramUniform3f(m_programId, m_rotationLocation, rotationX, rotationY, rotationZ);
}

void ShaderProgram::Use(void)
{
	glUseProgram(m_programId);
}