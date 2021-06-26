#include "glew.h"
#include "Utils.h"
#include "ShaderProgram.h"
#include <vector>

#pragma once
class WireframeObject
{
public:
	WireframeObject(vector<GLfloat> vertices, vector<GLfloat> colors);
	~WireframeObject(void);

	void Render(void);
	void SetRotation(GLfloat rotationX, GLfloat rotationY, GLfloat rotationZ);
private:
	vector<GLfloat> m_vertices;
	vector<GLfloat> m_colors;

	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_colorBuffer;

	ShaderProgram* m_shaderProgram;

	void CreateVBO(void);
	void DestroyVBO(void);
};

